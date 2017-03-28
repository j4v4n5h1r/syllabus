<?php

//admin users

function users_page() {
	$users = db_query("SELECT * FROM {users}");

	$header = array(
		'user_name' => 'User\'s Name',
		'email' => 'Email',
		'role' =>'Role',
		// 'user_status' => 'Status',
		// 'button' => 'Open'
		);

	$rows = array();
	foreach ($users as $user) {

		$role = "";
		$user_role = db_query("SELECT rid FROM {users_roles} WHERE uid = :uid", array(':uid' => $user -> uid)) -> fetchField();
		$role = db_query("SELECT {name} FROM {role} WHERE {rid} = :rid", array(':rid' => $user_role)) -> fetchField();

		// $status = "";
		// if ($result -> user_status == 0) {
		// 	$status = "Fill";
		// } else if ($result -> user_status == 1) {
		// 	$status = "Pending";
		// } else if ($result -> user_status == 2) {
		// 	$status = "Declined";
		// } else if ($result -> user_status == 3) {
		// 	$status = "Approved";
		// }
		if ($user -> uid != 0) {
			$rows[$user -> uid] = array(
			'uid' => $user -> uid,
			'user_name' => $user -> name,
			'email' => $user -> mail,
			'role' => $role,
			// 'user_status' => $status,
			// 'button' => '<a href="' . base_path() . 'syllabus_main/user_open?idx=' . $user -> uid . '">Open</a>'
			);
		}
	}

	$options = array();
	foreach ($rows as $row) {
		$options[$row['uid']] = array(
			'user_name' => $row['user_name'],
			'email' => $row['email'],
			'role' => $row['role'],
			// 'user_status' => $row['user_status'],
			// 'button' => $row['button']
			);
	}
	$form['table'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No users found'),
		);

	$form['submit_update'] = array(
		'#type' => 'submit',
		'#value' => t('Update'),
		'#submit' => array('users_page_submit_update'),
		);
	$form['submit_delete'] = array(
		'#type' => 'submit',
		'#value' => t('Delete'),
		'#submit' => array('users_page_submit_delete'),
		);

	return $form;
}

function users_page_submit_update($form, $form_state){
	$x = 0;
	$y = 0;
	foreach ($form_state['values']['table'] as $value) {
		if ($value != 0) {
			$y = $value;
			$x++;
		}
	}
	if ($x == 1) {
		drupal_goto('syllabus_main/user_update', array('query' => array('idx' => $y)));
	} else if ($x > 1) {
		drupal_set_message("Please select just one!");
	} else if ($x < 1) {
		drupal_set_message("Please select one!");
	}
}

function users_page_submit_delete($form, $form_state){
	$x = 0;
	foreach (($form_state['values']['table']) as $lines => $line) {
		if($line) {
			$x++;
			$delete = db_delete('users')
			->condition('uid', $line)
			-> execute();
		}
	}
	if ($x == 0) {
		drupal_set_message('No line selected!');
	}
}

function user_open() {
	drupal_set_message("Open");
}