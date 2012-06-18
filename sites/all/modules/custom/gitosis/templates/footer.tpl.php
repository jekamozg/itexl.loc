<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<div id="footer-main-1">
    <div class="footer-1">
        <div class="footer-about">
            <h1>About Flirpy</h1>
            <p><?php print variable_get('footer_about', '');?></p>
        </div>
        <div class="footer-follow">
            <h1>FOLLOW...</h1>
            <div class="footer-facebook">
                <a href="<?php print $facebook_link;?>" target="_blank">
                    <img src="<?php print base_path().drupal_get_path('module', 'itexl').'/images/facebook_icon.png';?>"/>
                </a>
            </div>
            <div class="footer-twitter">
                <a href="<?php print $twitter_link;?>" target="_blank">
                    <img src="<?php print base_path().drupal_get_path('module', 'itexl').'/images/twitter_icon.png';?>"/>
                </a>
            </div>
        </div>
    </div>
</div>
<div id="footer-main-2">
    <div class="footer-1">
        <div class="footer-about">
            <img src="<?php print base_path().drupal_get_path('module', 'itexl').'/images/flirpy_logo_f.png';?>" title="Flirpy" alt="Flirpy">
        </div>
        <div class="footer-follow"></div>
    </div>
</div>
<div id="footer-main-3">
    <div class="footer-1">
        <div class="footer-about"></div>
        <div style="margin-top: 8px;" class="footer-follow">Copyright © 2011 Flirpy</div>
    </div>
</div>