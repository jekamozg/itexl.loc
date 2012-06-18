<?php
// $Id$

/**
 * @file
 * Theme Functions
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 */
define('OM_BASE_THEME_PATH', drupal_get_path('theme', 'om'));  

include_once OM_BASE_THEME_PATH . '/inc/om_regions.inc'; 
include_once OM_BASE_THEME_PATH . '/inc/om_grids.inc'; 
include_once OM_BASE_THEME_PATH . '/inc/om_utils.inc'; 
include_once OM_BASE_THEME_PATH . '/inc/om_offline.inc'; 
include_once OM_BASE_THEME_PATH . '/inc/deprecated.inc'; 

/**
 * Implements HOOK_theme().
 *
function om_theme(&$existing, $type, $theme, $path) {
  //drupal_set_message("<pre>" . print_r($existing,true) . "</pre>");

  if ($type == 'theme') {
    dsm($existing, true);
  }
  return array();
}
*/

/**
 * Implementation of hook_theme().
 *
 */
function om_theme() {
  return array(
    'region' => array( /* @Legacy - soon will be deleted */
      'arguments' => array('region_name' => NULL, 'region' => NULL, 'region_classes' => NULL, 'region_inner' => 0),
    ),
    'identity' => array(
      'arguments' => array('logo' => NULL, 'site_name' => NULL, 'site_slogan' => NULL, 'front_page' => NULL),
    ),
    'content_elements' => array(
      'arguments' => array('mission' => NULL, 'tabs' => NULL, 'title' => NULL),
    ),    
    'search_box' => array(
      'arguments' => array('search_box' => NULL),
    ),  
    'menu' => array(
      'arguments' => array('menu_name' => NULL, 'menu' => NULL, 'menu_tree' => NULL),
    ),              
  );
}


/** 
 * Identity
 *
 * Grouped variables
 * - Logo
 * - Site Name
 * - Site Slogan
 *
 */
function om_identity($logo, $site_name, $site_slogan, $front_page) {
  if (!empty($logo) || !empty($site_name) || !empty($site_slogan)) { 
    $out = '<div id="logo-title">';
    if (!empty($logo)) $out .= '<a href="' . $front_page . '" title="' . t('Home') . '" rel="home" id="logo"><img src="' . $logo . '" alt="' . t('Home') . '" /></a>';
    if (!empty($site_name) || !empty($site_slogan)) { 
      $out .= '<div id="name-and-slogan">';
      if (!empty($site_name)) $out .= '<h2 id="site-name"><a href="' . $front_page . '" title="' . t('Home') . '" rel="home">' . $site_name . '</a></h2>';
      if (!empty($site_slogan)) $out .= '<div id="site-slogan">' . $site_slogan . '</div>';
      $out .= '</div> <!-- /#name-and-slogan -->';
    }    
    $out .= '</div> <!-- /#logo-title -->';
    return $out;
  }
}


/**
 * Content Elements
 *
 * Grouped variables
 * - Mission
 * - Tabs
 * - Title
 *
 */
function om_content_elements($mission = NULL, $tabs = NULL, $title = NULL) {
  $out = '';
  if (!empty($mission)) $out .= '<div id="mission">' . $mission .'</div>'; 
  if (!empty($tabs))    $out .= '<div id="page-tabs" class="tabs">' . $tabs .'</div>'; 
  if (!empty($title))   $out .= '<h1 id="page-title" class="title">' . preg_replace('/\[break\]/', '<br />', $title) . '</h1>'; 
  return $out;
}


/**
 * Breadcrumbs
 *
 * Adding markups
 *
 */
function om_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) return '<div id="page-breadcrumb" class="breadcrumb">' . implode(' » ', $breadcrumb) . '</div>'; 
}


/**
 * Search Box
 *
 * Adding markups
 *
 */
function om_search_box($search_box) {
  if (!empty($search_box)) return '<div id="search-box">' . $search_box . '</div>';
}


/**
 * Primary, Secondary Menus
 *
 * Adding markups
 *
 */
function om_menu($menu_name = NULL, $menu = NULL, $menu_tree = NULL) {
  if (!empty($menu)) return '<div id="menubar-' . $menu_name . '" class="menubar">' . $menu_tree . '</div>';
}


/**
 * Implementation of theme_menu_item()
 *
 * Overriding the menu item behavior
 *
 */
function om_menu_item($link, $has_children, $menu = '', $in_active_trail = FALSE, $extra_class = NULL) {
  $class = ($menu ? 'expanded' : ($has_children ? 'collapsed' : 'leaf'));
  
  if (!empty($extra_class)) $class .= ' ' . $extra_class;

  if ($in_active_trail) $class .= ' active-trail';
  
  return '<li class="' . $class . ' ' . $link . $menu . "</li>\n";  
}


/**
 * Implementation of theme_menu_item_link()
 *
 * Adding menu id to li tag classes and not to a tag
 *
 */
function om_menu_item_link($link) {
  if (empty($link['localized_options'])) $link['localized_options'] = array();

  // OM Tools integration  
  if (module_exists('om_tools')) {
    $om_tools_values = variable_get('om_tools', '');  
    if (isset($om_tools_values['menu']) && ($om_tools_values['menu']['menu_classes_switch'] == 1)) {  
      $class = $om_tools_values['menu']['menu_classes_' . $link['mlid']]; 
      $link['localized_options']['attributes']['class'] = $class;
    }
  }
  //dsm($link);
  if (isset($link['tab_root'])) {
    //This works for local tabs
    return l($link['title'], $link['href'], $link['localized_options']);
  }
  else {
    //This is for normal menus
    return 'menu-' . $link['mlid'] . '">' . l($link['title'], $link['href'], $link['localized_options']);
  }
}


/**
 * Implementation of template_preprocess_page()
 *
 */
function om_preprocess_page(&$vars) {
  global $theme; 
  global $theme_path; 

  // additional info settings
  $info = drupal_parse_info_file($theme_path . '/' . $theme . '.info');

  // get all region content, styles, scripts, grids
  om_region_process_variables($vars);
  
  // additional meta devices
  om_meta_get($vars, $info);
  
  // adding grids layout, guides for admin
  om_grids_page_vars($vars, $info);
  
  // activates om offline countdown
  om_offline($vars, $info);
    
  // this is to add any new js
  $vars['scripts'] = drupal_get_js();

  // aggregate css files
  om_aggregate_css($vars, $info);
        
  // body classes
  om_body_classes($vars, $info, NULL);
  
  // if om tools doesn't exist
  om_body_node_classes($vars);  

  // url paths as template files
  om_path_template($vars);
      
  // delete [break] in the head title
  $vars['head_title'] = preg_replace('/\[break\]/', '', $vars['head_title']);
  
  $vars['tabs2'] = menu_secondary_local_tasks();
  
  // change variable name
  $vars['main_menu'] = $vars['primary_links'];
  
  // change variable name
  $vars['secondary_menu'] = $vars['secondary_links'];
  //$vars['main_menu_tree'] = menu_tree(variable_get('menu_primary_links_source', 'primary-links'));
  
  // i18n module integration  
  if (!isset($vars['main_menu_tree']) && empty($vars['main_menu_tree'])) {
    if (module_exists('i18n') && function_exists('i18nmenu_translated_tree')) {
      $vars['main_menu_tree'] = i18nmenu_translated_tree(variable_get('menu_primary_links_source', 'primary-links'));
    }
    else {
      //Override main_menu_tree variable use:
      $vars['main_menu_array']  = menu_tree_page_data('primary-links');
      $vars['main_menu_tree'] = menu_tree_output($vars['main_menu_array']);
    }
  }

  if (module_exists('i18n') && function_exists('i18nmenu_translated_tree')) {
    $vars['secondary_menu_tree'] = i18nmenu_translated_tree(variable_get('menu_secondary_links_source', 'secondary-links'));
  }
  else {
    $vars['secondary_menu_tree'] = menu_tree(variable_get('menu_secondary_links_source', 'secondary-links'));
  }    
  
  // Hook into color.module
  if (module_exists('color')) _color_page_alter($vars); 
  
  date_default_timezone_set('UTC');
  
  $vars['closure'] .= '<div id="legal"><a href="http://www.drupal.org/project/om">OM Base Theme</a> ' . date('Y') . ' | V6.x-2.x | by <a href="http://www.danielhonrade.com">Daniel Honrade</a></div>';
 
  //dsm($vars);
}


/**
 * Implementation of template_preprocess_block()
 *
 */
function om_preprocess_block(&$vars, $hook) {
  $block = $vars['block'];
  $blocks = block_list($block->region);
  // Additional classes for blocks.
  $block_classes[] = 'block';
  $block_classes[] = 'block-' . $block->module;
  $block_classes[] = 'block-' . $vars['block_zebra'];
  
  $block_classes[] = 'block-' . $vars['block_id'];
  $block_classes[] = 'block-group-' . count($blocks);

  // Block Class Module
  if (module_exists('block_class')) $block_classes[] = block_class($block); 

  // OM Tools Module
  if (module_exists('om_tools') && isset($vars['om_block_classes'])) $block_classes[] = $vars['om_block_classes'];

  if ($vars['block_id'] == 1) $block_classes[] = 'block-first';
  if ($vars['block_id'] == count($blocks)) $block_classes[] = 'block-last';

  // Block Edit
  $vars['edit_block_array'] = array();
  $vars['edit_block'] = '';
  if (user_access('administer blocks')) {
    om_edit_block($vars, $hook);
    $block_classes[] = 'with-edit-block';
  } 
  // Aggregate block classes.
  $vars['block_classes'] = implode(' ', $block_classes); 
  //dsm($vars);
}




