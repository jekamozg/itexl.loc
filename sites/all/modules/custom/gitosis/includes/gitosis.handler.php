<?php

class Gitosis {

    var $gitosis_directory;
    var $key_extension = '.pub';
    var $repository;
    /**
     *
     * @param type $gitosis_conf - 
     * array('repository1' => 
     *          array(
     *              'members' => array(user1, user2), 
     *              'writable' => array(repository1, repository2),
     *          )
     * );
     * @return type gitosis.conf string
     */
    function generate_configuration($gitosis_conf) {
        $conf = "\n";
        foreach ($gitosis_conf as $key => $value) {
            $conf .= "[group $key]\n";
            foreach ($value as $attr_key => $attr_value) {
                if (is_array($attr_value)) {
                    $attr_value = implode(" ", $attr_value);
                }
                $conf .= "$attr_key = $attr_value\n";
            }
            $conf .= "\n";
        }
        return $conf;
    }

    function exec($command) {
        $execute = true;
        $execute_string = 'cd';
        $current_directory = $this->directory_path($this->gitosis_directory);
        if (strpos($command, 'clone') !== 0) {
            $current_directory = $this->gitosis_directory;
        }
        else if (file_exists($current_directory . DIRECTORY_SEPARATOR . 'gitosis.conf')) {
            $execute = false;
        }
        else {
//            $execute_string = '';
        }
        $execute_string .= " $current_directory\n git $command";
         if ($execute) {
            exec($execute_string, $output, $return);
//            var_dump(compact('execute_string' ,'output', 'return'));die;
            return compact('output', 'return');
         }
    }

    function message($output) {
        $return = 1;
        if (isset($output['output'][0])) {
            switch ($output['return']) {
                case 128:
                    $return = 'unknown';
                    break;
                case 0:
                    $return = 'success';
                    break;
            }
        } else {
            switch ($output['return']) {
                case 128:
                    if (file_exists($this->gitosis_directory . DIRECTORY_SEPARATOR . 'gitosis.conf'))
                        $return = 'clone';
                    else
                        $return = 'unknown';
                    break;
                case 0:
                    $return = 'success';
                    break;
            }
        }
        return $return;
    }

    
    
    function exists_directory() {
        return file_exists($this->gitosis_directory.DIRECTORY_SEPARATOR.'gitosis.conf');
    }
    
    function save_configuration($conf) {
        return file_put_contents($this->gitosis_directory.DIRECTORY_SEPARATOR.'gitosis.conf', $conf);
    }

    function add_pubkey($filename, $pubkey) {
        return file_put_contents($this->_get_filename_pubkey($filename), $pubkey);
    }
    
    function validate_pubkey($pubkey) {
        $return = false;
        $pattern = '#^ssh\-[a-z]{3}\s(\S+)\s\S+[^$]#';
        preg_match($pattern, $pubkey, $matches);
        if(isset($matches[0])) {
            $return = true;
        }
        return $return;
    }
    
    function exists_pubkey($filename) {
        return file_exists($this->_get_filename_pubkey($filename));
    }
    
    function remove_pubkey($filename) {
        return unlink($this->_get_filename_pubkey($filename));
    }
    
    function repository_name($project) {
        $connecting_array = explode(':', $this->repository);
        $repository_info = pathinfo($this->repository);
        return $connecting_array[0].':'.$project.'.'.$repository_info['extension'];
    }

    function directory_path() {
        $path = $this->gitosis_directory;
        $current_path = explode(DIRECTORY_SEPARATOR, $path);
        unset($current_path[count($current_path) - 1]);
        return implode(DIRECTORY_SEPARATOR, $current_path);
    }
    function _get_filename_pubkey($filename) {
        return ($this->gitosis_directory.DIRECTORY_SEPARATOR.'keydir'.DIRECTORY_SEPARATOR.$filename.$this->key_extension);
    }
}

?>
