<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
global $user;
?>
<div class="content_footer_buttons">
    <?php if($user->name == ''):?>
    <div class="subscribe_btn">
        <a href="<?php print base_path().'user/register';?>"></a>
    </div>
    <?php else:?>
    <div class="favorites_btn">
        <a href="javascript: void(0);">SAVED DISHES</a>
        <div class="favorites_list"><?php print theme('favorites', favorites_load_favorites($user->uid));?></div>
    </div>
    <?php endif;?>
    <div class="app_btn">
        <a href="<?php print base_path().'iphone_app.png';?>" rel="lightbox"></a>
    </div>
</div>