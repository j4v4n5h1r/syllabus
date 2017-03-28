<?php

//public courses

function my_courses() {
	global $user;
	$results = db_query("SELECT * FROM {syllabus_main_course} WHERE {coordinator}='" . $user -> uid . "'");

	$header = array(
		'course_name' => 'Course Name', 
		'course_teacher' => 'Teacher', 
		// 'course_status' => 'Status', 
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

		// $status = "";
		// if ($result -> status == 0) {
		// 	$status = "Fill";
		// } else if ($result -> status == 1) {
		// 	$status = "Pending";
		// } else if ($result -> status == 2) {
		// 	$status = "Declined";
		// } else if ($result -> status == 3) {
		// 	$status = "Approved";
		// }

		$rows[$result -> id] = array(
			'id' => $result -> id,
			'course_name' => $result -> name,
			'course_teacher' => $teacher,
			// 'course_status' => $status,
			'button' => '<a href="' . base_path() . 'syllabus_main/public_course?idx=' . $result -> id . '">View</a>'
			);
	}

	$options = array();
	foreach ($rows as $row) {
		$options[$row['id']] = array(
			'course_name' => $row['course_name'],
			'course_teacher' => $row['course_teacher'],
			// 'course_status' => $row['course_status'],
			'button' => $row['button']
			);
	}
	$form['table'] = array(
		'#type' => 'tableselect',
		'#header' => $header,
		'#options' => $options,
		'#empty' => t('No courses found'),
		);

	return $form;
}