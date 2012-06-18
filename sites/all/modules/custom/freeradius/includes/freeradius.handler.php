<?php

Class Freeradius {

    var $default_password;

    function insert_user($username, $password = false) {

        $query = "DELETE FROM radcheck WHERE username LIKE '$username'";
        db_query($query);
        $query = "INSERT INTO radcheck (username, attribute, op, value) VALUES ('$username', 'NT-Password', ':=', '$password')";
        return db_query($query);
    }

    function delete_user($username) {
        $query = "DELETE FROM radcheck WHERE username LIKE '$username'";
        return db_query($query);
    }

    function truncate_users($users) {
        if ($users) {
            $deleted = array();
            foreach ($users as $key => $value) {
                $deleted[] = "'$value'";
            }
            $deleted = implode(', ', $deleted);
            $query = "DELETE FROM radcheck WHERE username IN ($deleted)";
            return db_query($query);
        } else {
            return false;
        }
    }

    function add_users($users) {
        if ($users) {
            foreach ($users as $key => $value) {
                $query = "INSERT INTO radcheck (username, attribute, op, value) VALUES ('$value', 'NT-Password', ':=', '$this->default_password')";
                db_query($query);
            }
            return true;
        } else {
            return false;
        }
    }

    function nt_hash($str) {
        $str = iconv('UTF-8', 'UTF-16LE', $str);
        $MD4Hash = hash('md4', $str);
        $NTLMHash = strtolower($MD4Hash);
        return($NTLMHash);
    }

}

?>
