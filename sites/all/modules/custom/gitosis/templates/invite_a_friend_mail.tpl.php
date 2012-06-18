<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
</head>
<style>
    body > div {
        font-weight: 900;
    }
</style>
<body class="<?php print $classes; ?>" style="font-family: myriad-pro-condensed-1, myriad-pro-condensed-2, sans-serif !important;">
<div style="font-weight: 900;"><?php print $params['name'].' has invited you to '.$params['join'];?></div>
<div>Date: <?php print $params['date'];?></div>
<div>Time: <?php print $params['time'];?></div>
<div><?php print l($params['dish']->title, url($params['dish']->path, array('absolute' => TRUE)));?></div>
<img src="<?php print url($params['dish']->field_d_thumbnail[0]['filepath'], array('absolute' => TRUE));?>"/>
<div>Restaurant: <?php print $params['restaurant']->title;?></div>
<div>Restaurant URL: <?php print l($params['restaurant']->field_r_link[0]['url'], $params['restaurant']->field_r_link[0]['url'], array('absolute' => TRUE, 'external' => TRUE));?></div>
<div>Special: 
    <?php foreach ($params['restaurant']->field_r_special as $row):?>
        <span><?php print $row['value'].'  ';?></span>
    <?php endforeach;?>
</div>
<div>Price: <?php print $params['restaurant']->field_r_price[0]['value'];?></div>
<div>Hours of operation: 
    <?php foreach ($params['restaurant']->field_r_hours as $row):?>
        <span><?php print $row['value'].'  ';?></span>
    <?php endforeach;?>
</div>
<div>Telephone number: <?php print $params['restaurant']->field_telephone_number[0]['value'];?></div>
<div>Address: <?php print $params['restaurant']->location['street'].', '.$params['restaurant']->location['city'].', '.$params['restaurant']->location['province_name'];?></div>
<div>JOIN?</div>
<div>
    <span>
        <a href="<?php print url('invite_a_friend/yes/'.md5($params['uid']).'/'.md5($params['code']), array('absolute' => TRUE));?>">Yes</a>
    </span>   
    <span>
        <a href="<?php print url('invite_a_friend/no/'.md5($params['uid']).'/'.md5($params['code']), array('absolute' => TRUE));?>">No</a>
    </span>
</div>
</body>
</html>
