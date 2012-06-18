<?php
// $Id$

/**
 * @file
 * Theme Functions - Regions
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 */


/**
 * Get all region properties
 *
 * - Content
 * - Styles
 * - Scripts
 * - Grids, IDs, Classes
 *
 */
function om_region_process_variables(&$vars) {
  global $theme_path;
      
  if (!empty($vars['sidebar_first'])) $vars['layout'] = 'first';
  if (!empty($vars['sidebar_second'])) $vars['layout'] = ($vars['layout'] == 'first') ? 'both' : 'second';
    
  // Better processing of regions
  if (file_exists($theme_path . '/regions.php')) {
    include_once $theme_path . '/regions.php';

    $regions = om_regions_get_info();
    foreach ($regions as $region => $properties) {
      // this will just load non-empty regions
      if (isset($vars[$region]) && !empty($vars[$region])) {
        om_regions_file_get($vars, $region, 'css');
        om_regions_file_get($vars, $region, 'js');      
        $vars[$region . '_region'] = om_regions_process_info($vars['layout'], $vars[$region], $properties);
        $vars[$region . '_grid'] = isset($properties['grid']) ? $properties['grid']: '';
      }
      else {
        $vars[$region . '_region'] = '';
      }
    }
  }
}

 
/**
 * Process regions.php provided on theme
 *
 */
function om_regions_process_info($layout = NULL, $region = NULL, $properties = array()) {

  if ($region) { 
    $tag     = (isset($properties['tag']) && (($properties['tag'] != 'div') || !empty($properties['tag']))) ? $properties['tag']: 'div';
    $id      = $properties['id'];
    $classes = !empty($properties['class']) ? ' ' . $properties['class']: '';
    $inner   = $properties['inner'];
    $top     = $properties['top'];
    $bottom  = $properties['bottom'];
    
    $excluded = array('sidebar-first', 'sidebar-second');
		$grid_default = (isset($properties['grid']) && ($properties['grid'] != 0)) ? ' grid-' . $properties['grid']: '';
		
    // Add information about the number of sidebars.
    if (($layout == 'both') && !in_array($id, $excluded)) {
      $classes .= (isset($properties['grid-both']) && ($properties['grid-both'] != 0)) ? ' grid-' . $properties['grid-both']: $grid_default;
    }
    elseif (($layout == 'first') && !in_array($id, $excluded)) {
      $classes .= (isset($properties['grid-first']) && ($properties['grid-first'] != 0)) ? ' grid-' . $properties['grid-first']: $grid_default;
    }
    elseif (($layout == 'second') && !in_array($id, $excluded)) {
      $classes .= (isset($properties['grid-second']) && ($properties['grid-second'] != 0)) ? ' grid-' . $properties['grid-second']: $grid_default;
    }
    else {
      $classes .= $grid_default;
    }

    $div_top     = ($top) ? '<div class="region-top"><div class="region-top-left"></div><div class="region-top-right"></div></div>': '';
    $div_bottom  = ($bottom) ? '<div class="region-bottom"><div class="region-bottom-left"></div><div class="region-bottom-right"></div></div>': '';
        
    $div_prefix = '<' . $tag . ' id="' . $id . '" class="region region-' . $id . $classes . '">' . $div_top; 
    $div_suffix = '<div class="om-clearfix"></div>' . $div_bottom . '</' . $tag . '><!-- /#' . $id . ' -->'; 

    if ($inner) { 
      $div_prefix .= '<div id="' . $id . '-inner" class="region-inner">'; 
      $div_suffix = '<div class="om-clearfix"></div></div>' . $div_bottom . '</' . $tag . '><!-- /#' . $id . '-inner --><!-- /#' . $id . ' -->'; 
    }

    return $div_prefix . $region . $div_suffix;
  }
}


/**
 * Get region files
 *
 */  
function om_regions_file_get(&$vars, $file_name = NULL, $type = 'css') {
  //global $theme;
  global $theme_path;  

  if (file_exists($theme_path . '/' . $type . '/' . $file_name . '.' . $type)) {
    if ($type == 'js') drupal_add_js($theme_path . '/js/' . $file_name . '.js');
    if ($type == 'css') $vars['css']['all']['theme'][$theme_path . '/css/' . $file_name . '.css'] = TRUE;
  } 
} 




