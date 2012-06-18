<?php

function freeradius_user_page() {
    return drupal_get_form('freeradius_user_page_form');
}

function freeradius_user_page_form() {
    $form = array();
    $form['fieldset'] = array(
        '#type' => 'fieldset',
    );
    $form['fieldset']['pass'] = array(
        '#type' => 'password_confirm',
        '#description' => t('Provide a password for your radius account in both fields.'),
        '#required' => TRUE,
    );
    $form['fieldset']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    return $form;
}

function freeradius_user_page_form_submit(&$form, &$form_state) {
    global $user;
    $freeradius = _freeradius_load_handler();
    $password = $freeradius->nt_hash($form_state['values']['pass']);
    $test = $freeradius->insert_user($user->name, $password);
    drupal_set_message(t('Password has been saved'));
}

function freeradius_admin_page() {
    return drupal_get_form('freeradius_admin_page_form');
}

function freeradius_admin_page_form() {
    $form = array();
    $user_roles = user_roles(TRUE);

    $form['fieldset'] = array(
        '#type' => 'fieldset',
    );
    $form['fieldset']['roles'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Roles'),
        '#default_value' => variable_get('freeradius_roles', array(0)),
        '#options' => $user_roles,
        '#required' => TRUE,
    );
    $form['fieldset']['default_password'] = array(
        '#type' => 'password_confirm',
        '#description' => t('Provide a default password for the freeradius account in both fields.'),
        '#required' => TRUE,
    );
    $form['fieldset']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    return $form;
}

function freeradius_admin_page_form_submit(&$form, &$form_state) {
    $freeradius = _freeradius_load_handler();
    $roles = $form_state['values']['roles'];
    $pass = $freeradius->nt_hash($form_state['values']['default_password']);
    variable_set('freeradius_roles', $roles);
    if ($pass)
        variable_set('freeradius_default_password', $pass);
    drupal_set_message(t('Configuration saved'));
    
    $roles = variable_get('freeradius_roles', array(0));
    $query = array(
        "SELECT uid, name FROM {users}",
        "WHERE uid <> 0",
    );
    $result = db_query(implode(" ", $query));
    while ($row = db_fetch_array($result)) {
        if(freeradius_user_permissions($row['uid'])) {
          $users[] = $row['name'];  
        }
        else {
            $black_list[] = $row['name'];
        }
    }
    print_r($users);
    print_r($black_list);
    $freeradius->truncate_users(array_merge($black_list, $users));
    $freeradius->add_users($users);
    die;
}

?>
