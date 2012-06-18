<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

function gitosis_check_key($filename) {
    global $user;
    $gitosis = _gitosis_load_handler();
    $current_file = explode("_", $filename);
    if ($current_file[0] == $user->name) {
        $item = $current_file[1] . $gitosis->key_extension;
        return $item;
    }
    else {
        return false;
    }
}

function gitosis_delete_key($filename) {
    global $user;
    if(gitosis_check_key($filename)) {
//        var_dump($filename);die;
        $dir = variable_get('gitosis_directory', 'gitosis-admin') . '/keydir';
        file_delete($dir.'/'.$filename);
        drupal_set_message(t('Key successfully deleted'));
    }
    else {
        drupal_set_message('You not have this key');
    }
    drupal_goto('user/'.$user->uid.'/gitosis/');
}

function gitosis_user_page() {
    global $user;
    $output = '';
    $items = array();
    $header = array(
        array('data' => 'Name'),
        array('data' => 'Actions'),
        );
    $dir = variable_get('gitosis_directory', 'gitosis-admin') . '/keydir';
    if ($handle = opendir($dir)) {
        while (false !== ($entry = readdir($handle))) {
            if ($entry != "." && $entry != "..") {
                $current_file = gitosis_check_key($entry);
                if ($current_file) {
                    $current_array = array(
                        'name' => $current_file,
                        'actions' => l('Delete', 'user/'.$user->uid.'/gitosis/delete/'.$entry),
                    );
                    $items[]['data'] = $current_array;
                }
            }
        }
        closedir($handle);
    }

    
    $output .= l(t('Add Key'), 'user/'.$user->uid.'/gitosis/add');
    
    if($items) {
        $output .= theme_table($header, $items);
    }
//    $output .= theme_item_list($items);

    return $output;
}

function gitosis_add_user_page() {
    return drupal_get_form('gitosis_add_user_page_form');
}

function gitosis_user_page_form() {
    global $user;
//    $form = array();
//    $form
}

function gitosis_add_user_page_form() {
    global $user;
//    print_r($user);die;
    $form = array();
    $gitosis = _gitosis_load_handler();

    $form['#attributes'] = array('enctype' => "multipart/form-data");

    $form['gitosis'] = array(
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );
//    if ($gitosis->exists_pubkey($user->name)) {
//        $form['gitosis']['info'] = array(
//            '#type' => 'item',
//            '#value' => '<b>' . t('your public key') . '</b>: ' . $user->name . $gitosis->key_extension,
//        );
//        $form['gitosis']['delete'] = array(
//            '#type' => 'submit',
//            '#value' => t('Delete'),
//        );
//    } else {
    $form['gitosis']['name_key'] = array(
        '#type' => 'textfield',
        '#title' => t('Key name'),
        '#required' => TRUE,
    );
    $form['gitosis']['key'] = array(
        '#type' => 'textarea',
        '#title' => t('Public key'),
    );
    $form['gitosis']['file_key'] = array(
        '#type' => 'file',
        '#title' => t('Attach new file'),
        '#size' => 40
    );
    $form['gitosis']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
//    }
    return $form;
}

function gitosis_add_user_page_form_submit(&$form, &$form_state) {
    global $user;
    $gitosis = _gitosis_load_handler();

    $dir = variable_get('gitosis_directory', 'gitosis-admin') . '/keydir';

    $form_values = $form_state['values'];

    $pubkey_name = $user->name . '_' . str_replace("_", "-", $form_values['name_key']) . '_' . time();
    $current_filename = $dir . '/' . $pubkey_name . $gitosis->key_extension;

    if ($form_values['key']) {
        $gitosis->add_pubkey($pubkey_name, $form_values['key']);
    } else {
        if ($file = file_save_upload('file_key', array())) {
            copy($file->filepath, $current_filename);
            file_delete($file->filepath);
        }
    }

    if (file_exists($current_filename) && $gitosis->validate_pubkey(file_get_contents($current_filename))) {
        drupal_set_message(t('Your public key has been added'));
        drupal_goto('user/'.$user->uid.'/gitosis/');
    } else {
        file_delete($current_filename);
        drupal_set_message(t('Wrong public key'), 'error');
    }
}

function gitosis_admin_page($arg1) {
    return drupal_get_form('gitosis_admin_page_form_' . $arg1);
}

function gitosis_admin_page_form_repository() {
//    $gitosis = _gitosis_load_handler();
//    if($gitosis->exists_directory()) drupal_set_message(t('Repository exists'));
//    else drupal_set_message ('Repository does not exist', 'error');
    $form = array();
    $form['repository'] = array(
        '#type' => 'textfield',
        '#title' => t('Administrative repository'),
        '#default_value' => variable_get('gitosis_repository', ''),
        '#size' => 60,
        '#maxlength' => 128,
        '#required' => TRUE,
        '#description' => t('Example') . ': <i>git@hostname:gitosis-admin.git</i>',
    );
    $form['folder'] = array(
        '#type' => 'textfield',
        '#title' => t('Destination path'),
        '#default_value' => variable_get('gitosis_directory', 'gitosis-admin'),
        '#size' => 60,
        '#maxlength' => 128,
        '#required' => TRUE,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save')
    );
    return $form;
}

function gitosis_admin_page_form_repository_submit(&$form, &$form_state) {
    $folder = $form_state['values']['folder'];
    $gitosis = _gitosis_load_handler();
    $folder_info = pathinfo($folder);
    if ($folder_info['dirname'] !== '.') {
        $folder_info['dirname'] .= DIRECTORY_SEPARATOR;
        $folder = $folder_info['dirname'] . $folder_info['basename'];
    } else {
        $folder_info['dirname'] = '';
    }
    $repository = $form_state['values']['repository'];
    $gitosis->gitosis_directory = $folder;
    $clone_output = $gitosis->exec('clone ' . $repository);
    if ($clone_output) {
//        var_dump($clone_output);die;
        switch ($gitosis->message($clone_output)) {
            case 'unknown':
                drupal_set_message(t('Unsuccessful attempt to clone the repository'), 'error');
                break;
            case 'success':
                if (rename($folder_info['dirname'] . 'gitosis-admin', $gitosis->gitosis_directory)) {
                    $gitosis_conf = file_get_contents($folder . DIRECTORY_SEPARATOR . 'gitosis.conf');
                    variable_set('gitosis_conf', $gitosis_conf);
                    variable_set('gitosis_directory', $folder);
                    variable_set('gitosis_repository', $repository);
                    drupal_set_message(t('Repository cloned'));
                } else {
                    drupal_set_message(t('Check the permissions on the ') . ' ' . $folder_info['dirname'], 'error');
                }
                break;
        }
    } else {
        drupal_set_message(t('Repository already exists'));
    }

//    print_r($clone_output);die;
}

function _gitosis_get_content_types() {
    $content_type = content_types();
    foreach ($content_type as $key => $value) {
        $content_types[$key] = $key;
    }
    return $content_types;
}

function gitosis_admin_page_form_content() {
    $content_types = _gitosis_get_content_types();
    $form = array();
    $form['content_type'] = array(
        '#type' => 'radios',
        '#title' => t('Content type'),
        '#default_value' => variable_get('gitosis_content_type', ''),
        '#options' => $content_types,
        '#required' => TRUE,
    );
    $form['roles'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Roles'),
        '#default_value' => variable_get('gitosis_roles', array(0)),
        '#options' => user_roles(TRUE),
        '#required' => TRUE,
    );
    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save')
    );
    return $form;
}

function gitosis_admin_page_form_content_submit(&$form, &$form_state) {
    $roles = $form_state['values']['roles'];
    $content_type = $form_state['values']['content_type'];
    $field_name = 'field_gitosis_member';
    $param = array(
        'field_name' => $field_name,
        'type_name' => $content_type,
    );
    $field = array(
        'field_name' => $field_name,
        'type_name' => $content_type,
        'display_settings' => array(
            'weight' => '-3',
            'parent' => '',
            'label' => array(
                'format' => 'above',
            ),
            'teaser' => array(
                'format' => 'user_full_name',
                'exclude' => 0,
            ),
            'full' => array(
                'format' => 'user_full_name',
                'exclude' => 0,
            ),
            '4' => array(
                'format' => 'default',
                'exclude' => 0,
            ),
            'token' => array(
                'format' => 'default',
                'exclude' => 0,
            ),
        ),
        'widget_active' => '1',
        'type' => 'userreference',
        'required' => '0',
        'multiple' => '1',
        'module' => 'userreference',
        'active' => '1',
        'referenceable_roles' => $roles,
        'referenceable_status' => '1',
//        'advanced_view' => '',
//        'advanced_view_args' => '',
        'widget' => array(
//            'autocomplete_match' => 'contains',
//            'size' => '40',
            'reverse_link' => 1,
//            'default_value' => array(
//                '0' => array(
//                    'uid' => NULL,
//                    '_error_element' => 'default_value_widget][field_speakers][0][uid][uid',
//                ),
//            ),
            'default_value_php' => NULL,
            'label' => 'Gitosis members',
            'weight' => '-3',
            'description' => 'Check Gitosis project members',
            'type' => 'userreference_buttons',
            'module' => 'userreference',
        ),
    );

    module_load_include('inc', 'content', 'includes/content.crud');
    if (content_field_instance_read($param)) {
        content_field_instance_update($field);
    } else {
        content_field_instance_create($field);
    }
    variable_set('gitosis_content_type', $content_type);
    variable_set('gitosis_roles', $roles);
    variable_set('gitosis_field_name', $field_name);
    drupal_set_message(t('Configuration is saved'));
}

?>
