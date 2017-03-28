<?php

//hod courses

function hod_courses_page() {
	global $user;
	$department = db_query("SELECT {id} FROM {syllabus_main_department} WHERE {hod}='" . $user -> uid . "' LIMIT 1") -> fetchField();
	$results = db_query("SELECT * FROM {syllabus_main_course} WHERE {dep}='" . $department . "'");

	$header = array(
		'course_name' => 'Course Name', 
		'course_teacher' => 'Teacher', 
		'course_status' => 'Status', 
		'button' => 'View'
		);
	$rows = array();

	foreach ($results as $result) {
		$userx = db_query("SELECT * FROM {users} WHERE {uid}=" . $result -> coordinator . " LIMIT 1") -> fetchObject();
		if (isset($userx -> name)) {
			$teacher = $userx -> name;
		} else {
			$teacher = " / ";
		}

		$status = "";
		if ($result -> status == 0) {
			$status = "In Progress";
		} else if ($result -> status == 1) {
			$status = "Pending";
		} else if ($result -> status == 2) {
			$status = "Declined";
		} else if ($result -> status == 3) {
			$status = "Approved";
		}

		$rows[$result -> id] = array(
			'id' => $result -> id,
			'course_name' => $result -> name,
			'course_teacher' => $teacher,
			'course_status' => $status,
			'button' => '<a href="' . base_path() . 'syllabus_main/course_open?idx=' . $result -> id . '">View</a>'
			);
	}

	$options = array();
	foreach ($rows as $row) {
		$options[$row['id']] = array(
			'course_name' => $row['course_name'],
			'course_teacher' => $row['course_teacher'],
			'course_status' => $row['course_status'],
			'button' => $row['button']
			);
	}
	$form['table'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No courses found'),
		);

	// $form['submit_update'] = array(
	// 	'#type' => 'submit',
	// 	'#value' => t('Update'),
	// 	'#submit' => array('hod_courses_page_submit_update'),
	// 	);
	// $form['submit_delete'] = array(
	// 	'#type' => 'submit',
	// 	'#value' => t('Delete'),
	// 	'#submit' => array('hod_courses_page_submit_delete'),
	// 	);

	return $form;
}

// function hod_courses_page_submit_update($form, $form_state){
// 	$x = 0;
// 	$y = 0;
// 	foreach ($form_state['values']['table'] as $value) {
// 		if ($value != 0) {
// 			$y = $value;
// 			$x++;
// 		}
// 	}
// 	if ($x == 1) {
// 		drupal_goto('syllabus_main/course_update', array('query' => array('idx' => $y)));
// 	} else if ($x > 1) {
// 		drupal_set_message("Please select just one!");
// 	} else if ($x < 1) {
// 		drupal_set_message("Please select one!");
// 	}
// }

// function hod_courses_page_submit_delete($form, $form_state){
// 	$x = 0;
// 	foreach (($form_state['values']['table']) as $lines => $line) {
// 		if($line) {
// 			$x++;
// 			$delete = db_delete('syllabus_main_course')
// 			->condition('id', $line)
// 			-> execute();
// 		}
// 	}
// 	if ($x == 0) {
// 		drupal_set_message('No line selected!');
// 	}
// }