-- phpMyAdmin SQL Dump
-- version 3.4.2
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Дек 30 2011 г., 11:17
-- Версия сервера: 5.1.54
-- Версия PHP: 5.3.5-1ubuntu7.2

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `radius`
--

-- --------------------------------------------------------

--
-- Структура таблицы `cui`
--

CREATE TABLE IF NOT EXISTS `cui` (
  `clientipaddress` varchar(15) NOT NULL DEFAULT '',
  `callingstationid` varchar(50) NOT NULL DEFAULT '',
  `username` varchar(64) NOT NULL DEFAULT '',
  `cui` varchar(32) NOT NULL DEFAULT '',
  `creationdate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `lastaccounting` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`username`,`clientipaddress`,`callingstationid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Дамп данных таблицы `cui`
--

INSERT INTO `cui` (`clientipaddress`, `callingstationid`, `username`, `cui`, `creationdate`, `lastaccounting`) VALUES
('192.168.0.1', '00-21-63-7E-9E-26', 'usertest1', '', '2011-12-10 17:42:26', '0000-00-00 00:00:00'),
('192.168.0.1', '00-21-63-7E-9E-26', 'usertest2', '', '2011-12-10 18:52:52', '0000-00-00 00:00:00'),
('192.168.0.100', '', 'usertest1', '', '2011-12-10 18:56:36', '2011-12-10 18:56:36'),
('192.168.0.1', '00-22-B0-0A-D8-1E', 'usertest2', '', '2011-12-11 07:26:13', '0000-00-00 00:00:00'),
('192.168.0.1', '00-11-22-33-44-55', 'usertest2', '', '2011-12-11 07:34:33', '0000-00-00 00:00:00');

-- --------------------------------------------------------

--
-- Структура таблицы `nas`
--

CREATE TABLE IF NOT EXISTS `nas` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `nasname` varchar(128) NOT NULL,
  `shortname` varchar(32) DEFAULT NULL,
  `type` varchar(30) DEFAULT 'other',
  `ports` int(5) DEFAULT NULL,
  `secret` varchar(60) NOT NULL DEFAULT 'secret',
  `server` varchar(64) DEFAULT NULL,
  `community` varchar(50) DEFAULT NULL,
  `description` varchar(200) DEFAULT 'RADIUS Client',
  PRIMARY KEY (`id`),
  KEY `nasname` (`nasname`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2 ;

--
-- Дамп данных таблицы `nas`
--

INSERT INTO `nas` (`id`, `nasname`, `shortname`, `type`, `ports`, `secret`, `server`, `community`, `description`) VALUES
(1, '192.168.0.0/24', 'itexl-network', 'other', 1812, 'ite_company1234', NULL, NULL, 'RADIUS Client');

-- --------------------------------------------------------

--
-- Структура таблицы `radacct`
--

CREATE TABLE IF NOT EXISTS `radacct` (
  `radacctid` bigint(21) NOT NULL AUTO_INCREMENT,
  `acctsessionid` varchar(64) NOT NULL DEFAULT '',
  `acctuniqueid` varchar(32) NOT NULL DEFAULT '',
  `username` varchar(64) NOT NULL DEFAULT '',
  `groupname` varchar(64) NOT NULL DEFAULT '',
  `realm` varchar(64) DEFAULT '',
  `nasipaddress` varchar(15) NOT NULL DEFAULT '',
  `nasportid` varchar(15) DEFAULT NULL,
  `nasporttype` varchar(32) DEFAULT NULL,
  `acctstarttime` datetime DEFAULT NULL,
  `acctstoptime` datetime DEFAULT NULL,
  `acctsessiontime` int(12) DEFAULT NULL,
  `acctauthentic` varchar(32) DEFAULT NULL,
  `connectinfo_start` varchar(50) DEFAULT NULL,
  `connectinfo_stop` varchar(50) DEFAULT NULL,
  `acctinputoctets` bigint(20) DEFAULT NULL,
  `acctoutputoctets` bigint(20) DEFAULT NULL,
  `calledstationid` varchar(50) NOT NULL DEFAULT '',
  `callingstationid` varchar(50) NOT NULL DEFAULT '',
  `acctterminatecause` varchar(32) NOT NULL DEFAULT '',
  `servicetype` varchar(32) DEFAULT NULL,
  `framedprotocol` varchar(32) DEFAULT NULL,
  `framedipaddress` varchar(15) NOT NULL DEFAULT '',
  `acctstartdelay` int(12) DEFAULT NULL,
  `acctstopdelay` int(12) DEFAULT NULL,
  `xascendsessionsvrkey` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`radacctid`),
  KEY `username` (`username`),
  KEY `framedipaddress` (`framedipaddress`),
  KEY `acctsessionid` (`acctsessionid`),
  KEY `acctsessiontime` (`acctsessiontime`),
  KEY `acctuniqueid` (`acctuniqueid`),
  KEY `acctstarttime` (`acctstarttime`),
  KEY `acctstoptime` (`acctstoptime`),
  KEY `nasipaddress` (`nasipaddress`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `radcheck`
--

CREATE TABLE IF NOT EXISTS `radcheck` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(64) NOT NULL DEFAULT '',
  `attribute` varchar(64) NOT NULL DEFAULT '',
  `op` char(2) NOT NULL DEFAULT '==',
  `value` varchar(253) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `username` (`username`(32))
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `radcheck`
--

INSERT INTO `radcheck` (`id`, `username`, `attribute`, `op`, `value`) VALUES
(1, 'usertest1', 'Password', '==', 'usertest2'),
(3, 'usertest2', 'Password', '==', 'usertest1');

-- --------------------------------------------------------

--
-- Структура таблицы `radgroupcheck`
--

CREATE TABLE IF NOT EXISTS `radgroupcheck` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `groupname` varchar(64) NOT NULL DEFAULT '',
  `attribute` varchar(64) NOT NULL DEFAULT '',
  `op` char(2) NOT NULL DEFAULT '==',
  `value` varchar(253) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `groupname` (`groupname`(32))
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `radgroupreply`
--

CREATE TABLE IF NOT EXISTS `radgroupreply` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `groupname` varchar(64) NOT NULL DEFAULT '',
  `attribute` varchar(64) NOT NULL DEFAULT '',
  `op` char(2) NOT NULL DEFAULT '=',
  `value` varchar(253) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `groupname` (`groupname`(32))
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `radippool`
--

CREATE TABLE IF NOT EXISTS `radippool` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `pool_name` varchar(30) NOT NULL,
  `framedipaddress` varchar(15) NOT NULL DEFAULT '',
  `nasipaddress` varchar(15) NOT NULL DEFAULT '',
  `calledstationid` varchar(30) NOT NULL,
  `callingstationid` varchar(30) NOT NULL,
  `expiry_time` datetime DEFAULT NULL,
  `username` varchar(64) NOT NULL DEFAULT '',
  `pool_key` varchar(30) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `radippool_poolname_expire` (`pool_name`,`expiry_time`),
  KEY `framedipaddress` (`framedipaddress`),
  KEY `radippool_nasip_poolkey_ipaddress` (`nasipaddress`,`pool_key`,`framedipaddress`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `radpostauth`
--

CREATE TABLE IF NOT EXISTS `radpostauth` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(64) NOT NULL DEFAULT '',
  `pass` varchar(64) NOT NULL DEFAULT '',
  `reply` varchar(32) NOT NULL DEFAULT '',
  `authdate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=53 ;

--
-- Дамп данных таблицы `radpostauth`
--

INSERT INTO `radpostauth` (`id`, `username`, `pass`, `reply`, `authdate`) VALUES
(1, 'usertest1', '', 'Access-Reject', '2011-12-06 15:23:51'),
(2, 'usertest1', '', 'Access-Accept', '2011-12-06 15:25:15'),
(3, 'usertest1', '', 'Access-Accept', '2011-12-06 15:25:15'),
(4, 'usertest1', '', 'Access-Accept', '2011-12-06 15:28:53'),
(5, 'usertest1', '', 'Access-Accept', '2011-12-06 15:28:53'),
(6, 'usertest1', '', 'Access-Accept', '2011-12-06 15:29:40'),
(7, 'usertest1', '', 'Access-Reject', '2011-12-06 15:34:52'),
(8, 'usertest1', '', 'Access-Accept', '2011-12-06 15:37:09'),
(9, 'usertest1', '', 'Access-Accept', '2011-12-06 15:47:54'),
(10, 'usertest1', '', 'Access-Accept', '2011-12-06 16:10:55'),
(11, 'usertest1', '', 'Access-Accept', '2011-12-06 16:12:57'),
(12, 'usertest1', '', 'Access-Accept', '2011-12-10 16:48:04'),
(13, 'usertest1', '', 'Access-Accept', '2011-12-10 16:59:12'),
(14, 'usertest1', '', 'Access-Accept', '2011-12-10 17:13:28'),
(15, 'usertest1', '', 'Access-Accept', '2011-12-10 17:20:33'),
(16, 'usertest1', '', 'Access-Accept', '2011-12-10 17:25:35'),
(17, 'usertest1', '', 'Access-Reject', '2011-12-10 17:38:48'),
(18, 'usertest1', '', 'Access-Reject', '2011-12-10 17:39:09'),
(19, 'usertest1', '', 'Access-Reject', '2011-12-10 17:39:43'),
(20, 'usertest1', '', 'Access-Accept', '2011-12-10 17:42:26'),
(21, 'usertest1', '', 'Access-Accept', '2011-12-10 17:47:33'),
(22, 'usertest1', '', 'Access-Accept', '2011-12-10 18:02:56'),
(23, 'usertest1', '', 'Access-Accept', '2011-12-10 18:21:45'),
(24, 'usertest1', '', 'Access-Accept', '2011-12-10 18:23:54'),
(25, 'usertest1', '', 'Access-Accept', '2011-12-10 18:36:01'),
(26, 'usertest1', '', 'Access-Accept', '2011-12-10 18:41:23'),
(27, 'usertest1', '', 'Access-Accept', '2011-12-10 18:46:14'),
(28, 'usertest1', '', 'Access-Accept', '2011-12-10 18:48:22'),
(29, 'usertest2', '', 'Access-Accept', '2011-12-10 18:52:52'),
(30, 'usertest1', 'usertest2', 'Access-Accept', '2011-12-10 18:56:36'),
(31, 'usertest2', '', 'Access-Accept', '2011-12-10 19:16:20'),
(32, 'host/note', '', 'Access-Reject', '2011-12-10 19:30:46'),
(33, 'usertest1', '', 'Access-Accept', '2011-12-10 19:33:16'),
(34, 'usertest1', '', 'Access-Reject', '2011-12-10 19:37:12'),
(35, 'usertest1', '', 'Access-Reject', '2011-12-10 19:37:22'),
(36, 'usertest1', '', 'Access-Accept', '2011-12-10 19:37:41'),
(37, 'usertest1', '', 'Access-Accept', '2011-12-11 05:46:11'),
(38, 'usertest2', '', 'Access-Accept', '2011-12-11 07:26:13'),
(39, 'usertest2', '', 'Access-Accept', '2011-12-11 07:32:02'),
(40, 'usertest2', '', 'Access-Accept', '2011-12-11 07:34:33'),
(41, 'usertest2', '', 'Access-Accept', '2011-12-11 07:34:37'),
(42, 'usertest2', '', 'Access-Accept', '2011-12-11 07:35:30'),
(43, 'usertest2', '', 'Access-Accept', '2011-12-11 08:32:36'),
(44, 'usertest2', '', 'Access-Accept', '2011-12-11 09:33:11'),
(45, 'usertest2', '', 'Access-Accept', '2011-12-11 10:00:18'),
(46, 'usertest2', '', 'Access-Accept', '2011-12-11 11:46:18'),
(47, 'usertest1', '', 'Access-Accept', '2011-12-11 12:55:23'),
(48, 'usertest1', '', 'Access-Accept', '2011-12-11 13:56:06'),
(49, 'usertest1', '', 'Access-Accept', '2011-12-11 14:56:48'),
(50, 'usertest1', '', 'Access-Accept', '2011-12-11 15:57:30'),
(51, 'usertest1', '', 'Access-Accept', '2011-12-11 16:58:11'),
(52, 'usertest1', '', 'Access-Accept', '2011-12-14 13:59:55');

-- --------------------------------------------------------

--
-- Структура таблицы `radreply`
--

CREATE TABLE IF NOT EXISTS `radreply` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(64) NOT NULL DEFAULT '',
  `attribute` varchar(64) NOT NULL DEFAULT '',
  `op` char(2) NOT NULL DEFAULT '=',
  `value` varchar(253) NOT NULL DEFAULT '',
  PRIMARY KEY (`id`),
  KEY `username` (`username`(32))
) ENGINE=MyISAM DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `radusergroup`
--

CREATE TABLE IF NOT EXISTS `radusergroup` (
  `username` varchar(64) NOT NULL DEFAULT '',
  `groupname` varchar(64) NOT NULL DEFAULT '',
  `priority` int(11) NOT NULL DEFAULT '1',
  KEY `username` (`username`(32))
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
