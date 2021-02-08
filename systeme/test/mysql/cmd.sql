--  A exécuter une fois ! une foi la bd crée , elle est stocker sur un server
SET NAMES 'utf8';
CREATE DATABASE IF NOT EXISTS Application CHARACTER SET 'utf8';

USE Application;

CREATE TABLE IF NOT EXISTS User(
	pseudo VARCHAR(20) NOT NULL,
	password VARCHAR(20) NOT NUll,
	score INT NOT NULL DEFAULT 0,
	actif SMALLINT(1) NOT NULL DEFAULT 0,
	PRIMARY KEY (pseudo)
)
ENGINE=INNODB; 


--  mysqldump -u user -p --opt Application > Application.sql 
--  sauvegarde la base de donnée dans un fichier Application.sql

CREATE TABLE IF NOT EXISTS Friend(
	id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	pseudo_user VARCHAR(20) NOT NULL,
	pseudo_friend VARCHAR(20) NOT NULL,
	PRIMARY KEY (id)
)

CREATE TABLE IF NOT EXISTS Request(
	id SMALLINT UNSIGNED NOT NULL AUTO_INCREMENT,
	pseudo_dest VARCHAR(20) NOT NULL,
	pseudo_source VARCHAR(20) NOT NULL,
	PRIMARY KEY (id)
)

ENGINE=INNODB; -- liaison entre user
SHOW WARNINGS;