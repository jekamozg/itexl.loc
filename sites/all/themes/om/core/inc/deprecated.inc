<?php
// $Id$

/**
 * @file
 * Deprecated Functions
 *
 * @author: Daniel Honrade http://drupal.org/user/351112
 *
 * These will all soon be deleted in future versions,
 * please use the latest OM functions or new ways
 *
 */
 
/**
 * Legacy region processing
 * 
 */ 
function om_region($region_name = NULL, $region = NULL, $classes = NULL, $region_inner = 0) {

  if ($region) { 
    $id         = preg_replace('/_/', '-', $region_name);
    
    $div_prefix = '<div id="' . $id . '" class="region region-' . $id . ' ' . $classes . '">'; 
    $div_suffix = '<div class="om-clearfix"></div></div><!-- /#' . $id . ' -->'; 

    if ($region_inner == 1) { 
      $div_prefix .= '<div id="' . $id . '-inner" class="region-inner">'; 
      $div_suffix = '<div class="om-clearfix"></div></div><!-- /#' . $id . '-inner --></div><!-- /#' . $id . ' -->'; 
    }
    return $div_prefix . $region . $div_suffix;
  }
} 


/**
 * Legacy body_classes
 *
 * OM Tools has better body classes processing
 * 
 */ 
function om_body_node_classes(&$vars) {  
  
  // This  functionality will soon be transferred to OM Tools
  if (!module_exists('om_tools')) {

    $classes = explode(' ', $vars['body_classes']);
    
    if (!$vars['is_front']) {
    
      // Add unique class for each page.
      $path = drupal_get_path_alias($_GET['q']);
      
      // path title
      $classes[] = om_class_safe('page-' . $path);
      
      // default section
      list($section) = explode('/', $path, 2);

      $arg = arg(); // get all arguments

      if ($arg[0] == 'node') {
      
        $node_type = isset($vars['node']->type) ? $vars['node']->type: ''; 

        if (($arg[1] == 'add') && isset($arg[2])) { // add node
          $section      = 'node-add';                    
          $page_type    = $arg[2];                     
          $page_type_op = $page_type . '-add';         
        }
        elseif (($arg[1] == 'add') && !isset($arg[2])) { // add any node
          $section      = 'node-add';               
          $page_type    = 'any';                    
          $page_type_op = $page_type . '-add';           
        }          
        elseif (is_numeric($arg[1]) && !isset($arg[2]) && empty($node_type)) { // not found
          $section      = 'page-not-found';              
          $page_type    = 'any';                    
          $page_type_op = $page_type . '-view';         
        }
        elseif (is_numeric($arg[1]) && !isset($arg[2])) { // view node
          // default $section                        
          $page_type    = $node_type;                  
          $page_type_op = $page_type . '-view';          
        } 
        elseif (is_numeric($arg[1]) && isset($arg[2])) { // has arg 2, like delete, edit, etc.
          $section      = 'node-' . $arg[2];               
          $page_type    = !empty($node_type) ? $node_type: 'any';                   
          $page_type_op = $page_type . '-' . $arg[2];          
        }    
        $classes[] = om_class_safe('content-type-' . $page_type);
        $classes[] = om_class_safe('content-type-' . $page_type_op);
      }
      $classes[] = om_class_safe('section-' . $section);
    }
    $vars['body_classes_array'] = $classes;
    $vars['body_classes'] = implode(' ', $classes); // Concatenate with spaces.	
  }
} 


