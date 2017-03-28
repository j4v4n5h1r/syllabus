<?php

//HoD new user

function new_user_page() {
	$form["user_name"] = array(
		'#type' => 'textfield',
		'#title' => t("User Name"),
		'#required' => TRUE
		);
	$form["email"] = array(
		'#type' => 'textfield',
		'#title' => t("Email Adress"),
		'#required' => TRUE
		);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Add User',
		);

	return $form;
}

function new_user_page_submit($form, $form_state){
	$rid = 6; //its staff role id
	$uid = db_query("SELECT {uid} FROM {users} ORDER BY {uid} DESC LIMIT 1") -> fetchField();
	$id = db_insert('users') -> fields(array(
		'uid' => $uid + 1,
		'name' => $form_state['values']['user_name'],
		'mail' => $form_state['values']['email']
		)) -> execute();
	$idx = db_insert('users_roles') -> fields(array(
		'uid' => $uid + 1,
		'rid' => $rid
		)) -> execute();
	drupal_set_message('New User has been created!');
}