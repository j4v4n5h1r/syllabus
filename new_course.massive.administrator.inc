<?php

// admin mass new course

function mass_new_course_page() {
	$form['cname'] = array(
		'#title' => t('Course Name'), 
		'#type' => 'textarea', 
		'#value' => isset($context['cname']) ? drupal_implode_tags($context['cname']) : '',);
	$form['ccoordinator'] = array(
		'#title' => t('Course Coordinator'), 
		'#type' => 'textarea',
		'#value' => isset($context['ccoordinator']) ? drupal_implode_tags($context['ccoordinator']) : '',);
	$form['cteacher'] = array(
		'#title' => t('Academic Teacher'), 
		'#type' => 'textarea',
		'#value' => isset($context['cteacher']) ? drupal_implode_tags($context['cteacher']) : '',);
	$form['cetcs'] = array(
		'#title' => t('ETCS'), 
		'#type' => 'textarea',
		'#value' => isset($context['cetcs']) ? drupal_implode_tags($context['cetcs']) : '',);
	$form['cprofile'] = array(
		'#title' => t('Study Profile'), 
		'#type' => 'textarea',
		'#value' => isset($context['cprofile']) ? drupal_implode_tags($context['cprofile']) : '',);
	$form['mass_course_manage_teaching_methods'] = array(
		'#type' => 'fieldset',
		'#title' => t("Teaching methods and student-teacher contact hours")
		);
	$form['mass_course_manage_teaching_methods']['chours'] = array(
		'#title' => t('Number of Hours'), 
		'#type' => 'textarea',
		'#value' => isset($context['chours']) ? drupal_implode_tags($context['chours']) : '',);
	$form['mass_course_manage_teaching_methods']['clectures'] = array(
		'#title' => t('Lectures and Practicals'), 
		'#type' => 'textarea',
		'#value' => isset($context['clectures']) ? drupal_implode_tags($context['clectures']) : '',);
	$form['mass_course_manage_teaching_methods']['claboratories'] = array(
		'#title' => t('Laboratories'), 
		'#type' => 'textarea',
		'#value' => isset($context['claboratories']) ? drupal_implode_tags($context['claboratories']) : '',);
	$form['mass_course_manage_teaching_methods']['csessions'] = array(
		'#title' => t('Discussion Sessions'), 
		'#type' => 'textarea',
		'#value' => isset($context['csessions']) ? drupal_implode_tags($context['csessions']) : '',);
	$form['mass_course_manage_teaching_methods']['cseminars'] = array(
		'#title' => t('Seminars'), 
		'#type' => 'textarea',
		'#value' => isset($context['cseminars']) ? drupal_implode_tags($context['cseminars']) : '',);
	$form['mass_course_manage_teaching_methods']['cworkshop'] = array(
		'#title' => t('Work-shops'), 
		'#type' => 'textarea',
		'#value' => isset($context['cworkshop']) ? drupal_implode_tags($context['cworkshop']) : '',);
	$form['mass_course_manage_teaching_methods']['celearning'] = array(
		'#title' => t('eLearning'), 
		'#type' => 'textarea',
		'#value' => isset($context['celearning']) ? drupal_implode_tags($context['celearning']) : '',);

	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Create Courses',
		'#submit' => array('new_department_get_form'),
		);

	return $form;
}