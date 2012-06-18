<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//print_r($content);
?>
<?php if ($content != ''):?>
<table>
    <thead>
        <tr>
            <th>E-mail</th>
            <th>Date</th>
            <th>Time</th>
            <th>Accepted</th>
            <th></th>
        </tr>
    </thead>
    <tbody>
        <?php foreach($content as $key => $row):?>
        <?php if ($key % 2 == 0) $row_style = 'odd'; else $row_style='even';?>
        <tr class="<?php print $row_style;?>">
            <td><?php print $row['mail']?></td>
            <td><?php print $row['date']?></td>
            <td><?php print $row['time']?></td>
            <td><?php print $row['status']?></td>
            <td><?php print $row['join']?></td>
        </tr>
        <?php endforeach;?>
    </tbody>
</table>
<?php endif;?>