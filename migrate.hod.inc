<?php

function migrate_page() {
	$form['migrate_manage']["add"][0] = array(
		'#type' => 'select',
		'#title' => t('Title'),
		'#options' => array(
			0 => t('2014'),
			1 => t('2015'),
			2 => t('2016'))
		);
	$form['migrate_manage']["add"][1] = array(
		'#type' => 'select',
		'#title' => t('Title'),
		'#options' => array(
			0 => t('2017'),
			1 => t('2018'),
			2 => t('2019'))
		);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Migrate',
		'#submit' => array('new_department_get_form'),
		);

	return $form;
}