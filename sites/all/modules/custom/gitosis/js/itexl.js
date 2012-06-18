function fav_display(fav_flag) {
    if (fav_flag == 0) {
        $('.item-list', '.block-favorites').fadeIn();
        fav_flag = 1;
    }
    if (fav_flag == 1) {
        $('.item-list', '.block-favorites').fadeOut();
    }
}

function set_prevnext() {
    var next_href = $('.view-id-dishes .pager .pager-next a').attr('href');
    $('.view-id-dishes .pager .pager-next').css('display', 'none');
    var prev_href = $('.view-id-dishes .pager .pager-previous a').attr('href');
    $('.view-id-dishes .pager .pager-previous').css('display', 'none');
    var main_height = $('#main-wrapper').height();
//    console.log(main_width);
    $('.view-id-dishes .pager .pager-first a').text('«');
    $('.view-id-dishes .pager .pager-last a').text('»');
    $('.pn_buttons').css('margin-top', (main_height/2 - 100)+'px');
    if (next_href) {
        $('.pn_buttons').append('<a id ="next_new" href=""></a>');
        $('.pn_buttons #next_new').attr({
            href: next_href
        });
    }//console.log(next_href);
    if (prev_href) {
        $('.pn_buttons').append('<a id ="previous_new" href=""></a>');
        $('.pn_buttons #previous_new').attr({
            href: prev_href
        });
    }//console.log(prev_href);
}

$(document).ready(function(){
    set_prevnext();
//   voice
    var uv = document.createElement('script'); uv.type = 'text/javascript'; uv.async = true;
    uv.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + 'widget.uservoice.com/hsqL9gIX2fbO5XUMS0A.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(uv, s);
// end voice
   $('.dish-gallery img').click(function(){
       $('#dish-thumbnail').html('<img src="'+$(this).attr('src')+'"/>');
   });
   
   var fav_flag = 0;
   //add to my favorites
   $('.block-favorites .item-list').fadeOut();
   $('.block-favorites h2').click(function(){
        if (fav_flag == 0) {
            $('.item-list', '.block-favorites').fadeIn();
            fav_flag = 1;
        }
        else if (fav_flag == 1) {
            $('.item-list', '.block-favorites').fadeOut();
            fav_flag = 0;
        }
       
   });
   
   //SAVED DISHES
   var saved_dishes_flag = 0;
   //add to my favorites
//   $('.invite_a_friend_form').hide();
   $('.favorites_btn').click(function(){
        if (saved_dishes_flag == 0) {
            var favorites_list_height = $('.favorites_list').height()+75;
            $('.favorites_list').fadeIn().css({
                marginTop: -favorites_list_height+"px"
            });
            saved_dishes_flag = 1;
        }
        else if (saved_dishes_flag == 1) {
            $('.favorites_list').fadeOut();
            saved_dishes_flag = 0;
        }
       
   });
   var invite_flag = 0
   $('.invite_a_friend').click(function(){
        if (invite_flag == 0) {
            var favorites_list_height = $('.favorites_list').height();
            $('.invite_a_friend_form').slideDown();
            invite_flag = 1;
        }
        else if (invite_flag == 1) {
            $('.invite_a_friend_form').slideUp();
            invite_flag = 0;
        }
       
   });
   
   $('.invite_a_friend_form input[type="submit"]').click(function(){
       $('.invite_a_friend_form').slideUp();
   });
   //endinvite a friend
});