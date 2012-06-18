<?php
// $Id$

/**
 * @file
 * Theme Functions - Utilities
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 */

function om_edit_block(&$vars, $hook) {
  $block = $vars['block'];
  // Display 'edit block' for custom blocks.
  if ($block->module == 'block') {
    $vars['edit_block_array'][] = l( t('edit block'), 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
      array(
        'attributes' => array(
          'title' => t('Edit this block\'s content.'),
          'class' => 'block-edit',
        ),
        'query' => drupal_get_destination(),
        'html' => TRUE,
      )
    );
  }
  // Display 'configure' for other blocks.
  else {
    $vars['edit_block_array'][] = l( t('configure'), 'admin/build/block/configure/' . $block->module . '/' . $block->delta,
      array(
        'attributes' => array(
          'title' => t('Configure ' . $block->subject),
          'class' => 'block-config',
        ),
        'query' => drupal_get_destination(),
        'html' => TRUE,
      )
    );
  }
  // Display 'edit view' for Views blocks.
  if ($block->module == 'views' && user_access('administer views')) {
    list($view_name, $view_block) = explode('-block', $block->delta);
    $vars['edit_block_array'][] = l( t('edit view'), 'admin/build/views/edit/' . $view_name,
      array(
        'attributes' => array(
          'title' => t('Edit this view.'),
          'class' => 'block-edit-view',
        ),
        'query' => drupal_get_destination(),
        'fragment' => 'views-tab-block' . $view_block,
        'html' => TRUE,
      )
    );
  }
  // Display 'edit menu' for Menu blocks.
  elseif (($block->module == 'menu' || ($block->module == 'user' && $block->delta == 1)) && user_access('administer menu')) {
    $menu_name = ($block->module == 'user') ? 'navigation' : $block->delta;
    $vars['edit_block_array'][] = l( t('edit menu'), 'admin/build/menu-customize/' . $menu_name,
      array(
        'attributes' => array(
          'title' => t('Edit this menu.'),
          'class' => 'block-edit-menu',
        ),
        'query' => drupal_get_destination(),
        'html' => TRUE,
      )
    );
  }
  // Display 'edit menu' for Menu block blocks.
  elseif ($block->module == 'menu_block' && user_access('administer menu')) {
    list($menu_name, ) = split(':', variable_get("menu_block_{$block->delta}_parent", 'navigation:0'));
    $vars['edit_block_array'][] = l( t('edit menu'), 'admin/build/menu-customize/' . $menu_name,
      array(
        'attributes' => array(
          'title' => t('Edit this menu.'),
          'class' => 'block-edit-menu',
        ),
        'query' => drupal_get_destination(),
        'html' => TRUE,
      )
    );
  }
  $vars['edit_block'] = '<div class="edit-block">' . implode(' ', $vars['edit_block_array']) . '</div>';
}


/**
 * Override IE 30 stylesheet limit
 *
 * Aggregate css files
 *
 */
function om_aggregate_css(&$vars, $info = array()) {
  if (isset($info['settings']['css_aggregation']) && ($info['settings']['css_aggregation'] == 'on')) {  
    $preprocess_css = variable_get('preprocess_css', 0);
    $query_string = '?' . substr(variable_get('css_js_query_string', '0'), 0, 1);
    if (!$preprocess_css) {
      $styles = '';
      foreach ($vars['css'] as $media => $types) {
        $import = '';
        $counter = 0;
        foreach ($types as $files) {
          foreach ($files as $css => $preprocess) {
            $import .= '@import "'. base_path() . $css . $query_string .'";'."\n";
            $counter++;
            if ($counter == 15) {
              $styles .= "\n".'<style type="text/css" media="'. $media .'" rel="stylesheet">'."\n". $import .'</style>';
              $import = '';
              $counter = 0;
            }
          }
        }
        if ($import) $styles .= "\n".'<style type="text/css" media="'. $media .'" rel="stylesheet">'."\n". $import .'</style>';
      }
      if ($styles) $vars['styles'] = $styles;
    }
  }
}
  
  
/**
 * Body Classes
 *
 * - Browser classes
 *
 */
function om_body_classes(&$vars, $info = array(), $agent = NULL) {

  // kill the old left & right sidebars effect on body classes
  $old_sidebars = array('no-sidebars', 'two-sidebars', 'one-sidebar', 'sidebar-left', 'sidebar-right');
  foreach ($old_sidebars as $old_sidebars_key => $old_sidebars_class) {
    $vars['body_classes'] = str_replace($old_sidebars_class, '', $vars['body_classes']);
  }
  
  // Add information about the number of sidebars.
  if ($vars['layout'] == 'both') {
    $vars['body_classes'] .= ' two-sidebars';
  }
  elseif ($vars['layout'] == 'none') {
    $vars['body_classes'] .= ' no-sidebars';
  }
  else {
    $vars['body_classes'] .= ' one-sidebar sidebar-' . $vars['layout'];
  }

  if (isset($info['settings']['browsers']['class']) && ($info['settings']['browsers']['class'] == 'on')) {
    // Default known browsers
    $known_browsers = explode(',', preg_replace('/ /', '', $info['settings']['browsers']['known']));
    $agent = strtolower($agent ? $agent : $_SERVER['HTTP_USER_AGENT']);
    $pattern = '#(?<browser>' . join('|', $known_browsers) . ')[/ ]+(?<version>[0-9]+(?:\.[0-9]+)?)#';
  
    if (!preg_match_all($pattern, $agent, $matches)) return array();
    $i = count($matches['browser'])-1;
  
    $browser = array();
    $browser['browser'] = isset($matches['browser'][$i]) ? ' browser-' . om_class_safe($matches['browser'][$i]): '';
    $browser['version'] = (isset($matches['browser'][$i]) && isset($matches['version'][$i])) ? ' browser-' . om_class_safe($matches['browser'][$i]) . '-' . om_class_safe($matches['version'][$i]): '';  

    $vars['body_classes'] .= $browser['browser'];
    $vars['body_classes'] .= $browser['version'];
  }
}


/**
 * Additional Meta from Info file
 *
 */
function om_meta_get(&$vars, $info) { 

  $meta = isset($info['head']['meta']) ? $info['head']['meta']: FALSE; 
  if ($meta) {
    foreach ($meta as $name => $contents) {
      if (is_array($contents)) {
        $content = '';
        $ctotal = count($contents);
        $ccount = 0;
        foreach ($contents as $ckey => $cval) {
          $ccount++;
          $csep = ($ctotal != $ccount) ? ', ': '';
          $content .= $ckey . '=' . $cval . $csep;   
        }
      }
      else {
        $content = $contents;
      }
      $diff_keys = array('cleartype', 'X-UA-Compatible');
      $name_key = (!in_array($name, $diff_keys)) ? 'name': 'http-equiv';
      $vars['head'] .= '<meta ' . $name_key . '="' . $name . '" content="' . $content . '"/>' . "\n";  
    }
  } 
}


/**
 * Converts a string to a suitable html ID attribute.
 *
 * http://www.w3.org/TR/html4/struct/global.html#h-7.5.2 specifies what makes a
 * valid ID attribute in HTML. This function:
 *
 * - Ensure an ID starts with an alpha character by optionally adding an 'id'.
 * - Replaces any character except alphanumeric characters with dashes.
 * - Converts entire string to lowercase.
 *
 * @param $string
 *   The string
 * @return
 *   The converted string
 */
function om_class_safe($string) {
  // Replace with dashes anything that isn't A-Z, numbers, dashes, or underscores.
  return strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $string));
}


/**
 * Pate Templates
 *
 * Recognize url aliases as file page templates, ex. page-title.tpl.php
 *
 */
function om_path_template(&$vars) {
 
  if (module_exists('path')) {
    $alias = drupal_get_path_alias(str_replace('/edit', '', $_GET['q']));
    if ($alias != $_GET['q']) {
      $template_filename = 'page';
      foreach (explode('/', $alias) as $path_part) {
        $template_filename = $template_filename . '-' . $path_part;
        $vars['template_files'][] = $template_filename;
      }
    }
  }
}

  
/**
 * Generates IE CSS links for LTR and RTL languages.
 *
 * <!--[if IE  ]><?php print om_get_ie_styles('ie'); ?><![endif]-->
 * <!--[if IE 6]><?php print om_get_ie_styles('ie6'); ?><![endif]-->
 * <!--[if IE 7]><?php print om_get_ie_styles('ie7'); ?><![endif]-->
 * <!--[if IE 8]><?php print om_get_ie_styles('ie8'); ?><![endif]-->
 * <!--[if IE 9]><?php print om_get_ie_styles('ie9'); ?><![endif]-->
 */

function om_get_ie_styles($ie = NULL) {
  global $language;
  global $theme_path;
  
  $iecss = '';
  
  if (empty($ie)) {
    // depends on files
    $ies = array('ie', 'ie6', 'ie7', 'ie8', 'ie9');
  
    foreach ($ies as $key => $ie) {
      if (file_exists($theme_path . '/css/' . $ie . '.css')) {
        switch ($ie) {
          case  'ie': $num = ''; break;
          case 'ie6': $num =  6; break;
          case 'ie7': $num =  7; break;
          case 'ie8': $num =  8; break;
          case 'ie9': $num =  9; break;  
             default: $num = ''; break;                     
        }
        $iecss .= '<!--[if IE ' . $num . ']><link type="text/css" rel="stylesheet" media="all" href="' . base_path() . $theme_path . '/css/' . $ie . '.css" /><![endif]-->' . "\n";
      }
    }
  }
  else {
    // depends on head declaration
    $iecss = '<link type="text/css" rel="stylesheet" media="all" href="' . base_path() . $theme_path . '/css/' . $ie . '.css" />';
  }  
  if ($language->direction == LANGUAGE_RTL) $iecss .= '<style type="text/css" media="all">@import "'. base_path() . $theme_path .'/css/ie-rtl.css";</style>';  

  return $iecss;
}
 
