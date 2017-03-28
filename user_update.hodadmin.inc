<?php

function user_update() {
	$idx = filter_input(INPUT_GET, 'idx');
	$results = db_query("SELECT * FROM {users} WHERE {uid}=" . $idx . " LIMIT 1") -> fetchObject();

	$form["name"] = array(
		'#type' => 'textfield',
		'#title' => t("User Name"),
		'#default_value' => $results -> name,
		'#required' => TRUE
		);
	$form["mail"] = array(
		'#type' => 'textfield',
		'#title' => t("Email Adress"),
		'#default_value' => $results -> mail,
		'#required' => TRUE
		);

	$form['submit_save'] = array(
		'#type' => 'submit',
		'#value' => t('Save'),
		'#submit' => array('user_update_submit_save'),
		);
	$form['submit_cancel'] = array(
		'#type' => 'submit',
		'#value' => t('Cancel'),
		'#submit' => array('user_update_submit_cancel'),
		);

	return $form;
}

function user_update_submit_save($form, $form_state){
	$idx = filter_input(INPUT_GET, 'idx');
	if (db_query("UPDATE {users} SET {name}='" . $form_state['values']['name'] . "', {mail}='" . $form_state['values']['mail'] . "' WHERE {uid}=" . $idx)) {
		drupal_goto('syllabus_main');
	} else {
		drupal_set_message('Some Problem!');
	}
}

function user_update_submit_cancel($form, $form_state){
	drupal_goto('syllabus_main');
}