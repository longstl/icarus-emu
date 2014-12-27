<?php
$dbhost	= "127.0.0.1";
$dbuser = "root";	
$dbpassword = "152958";
$dbname = "iemu_ls";


if (isset($_POST['login']) && isset($_POST['password']))
{
	$login = $_POST['login'];
	$password = md5($_POST['password']);
	if (strlen($login) <= 32)
		if ($msconn = @mysql_connect($dbhost, $dbuser, $dbpassword))
			if(!@MYSQL_SELECT_DB($dbname))
			{
				echo 'Работа сайта временно приостановлена (Error: 101).';
				exit();
			}
	
	$mdpass = md5($login).$password;
	$query = "REPLACE INTO `accounts` SET `login`='".$login."', `password`='".$mdpass."', email= 'mail@mail.ru';";

	@mysql_query( $query );
	echo 'ok';

}

?>





<form action="reg.php" method="POST">
<b>Логин:</b><input type="text" name="login"><br/>
<b>Пароль:</b>&nbsp;<input type="password" name="password" /><br/>
<input type="submit" value="Зарегистрировать">
</form>

