<!DOCTYPE html>
<html lang="<?php print $language->language ?>" dir="<?php print $language->dir ?>">
<head>
	<?php print $head; ?>
	<title><?php print $head_title; ?></title>
	<?php print $styles; ?>
	<?php print om_get_ie_styles(); ?>
	<?php print $scripts; ?>
  <!--[if lt IE 9]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->	
</head>
<body class="<?php print $body_classes; ?>">
<div class="wrapper-outer">
	<header id="header" class="wrapper wrapper-header"><div class="wrapper-inner">
		<?php print theme('identity', $logo, $site_name, $site_slogan, $front_page); ?>
		<?php print $header_block_region; ?>
		<?php print theme('search_box', $search_box); ?>
    <div class="om-clearfix"></div>
	</div></header><!-- /#header-inner, /header -->
	<nav id="nav" class="wrapper wrapper-nav"><div class="wrapper-inner">
		<?php print theme('menu', 'main-menu', $main_menu, $main_menu_tree); ?>
		<?php print theme('menu', 'secondary-menu', $secondary_menu, $secondary_menu_tree); ?>
		<?php print $menu_bar_region; ?>
	</div></nav><!-- /.wrapper-inner, /nav -->
	<?php print $highlighted_region; ?>
	<div class="wrapper wrapper-main"><div class="wrapper-inner">
		<?php print $sidebar_first_region; ?>
		<div class="wrapper wrapper-middle<?php print $wrapper_middle_grid; ?>">
			<?php print $breadcrumb; ?>
			<div class="wrapper-inner">
				<?php print theme('content_elements', $mission, $tabs, $title) ?>
				<?php print $help; ?>
				<?php print $messages; ?>
				<?php print $content_region; ?>
				<?php print $feed_icons; ?>
			</div><!-- /.wrapper-inner -->
		</div><!-- /.wrapper-middle -->
		<?php print $sidebar_second_region; ?>		
    <div class="om-clearfix"></div>
	</div></div><!-- /.wrapper-inner, /.wrapper-main -->
	<footer class="wrapper wrapper-footer"><div class="wrapper-inner">
		<?php print $footer_region; ?>
		<?php print $footer_message_region; ?>
	</div></footer><!-- /.wrapper-inner, /footer -->
</div><!-- /.wrapper-outer -->
<?php print $closure; ?>

</body>
</html>
