<?php

function public_course() {
	drupal_add_css('http://code.jquery.com/ui/1.11.4/themes/smoothness/jquery-ui.css', 'external');
	drupal_add_js('http://code.jquery.com/jquery-1.10.2.js', 'external');
	drupal_add_js('http://code.jquery.com/ui/1.11.4/jquery-ui.js', 'external');

	$idx = filter_input(INPUT_GET, 'idx');
	$results = db_query("SELECT * FROM {syllabus_main_course} WHERE {id}=" . $idx . " LIMIT 1") -> fetchObject();
	$department = db_query("SELECT {department_name} FROM {syllabus_main_department} WHERE {id}=" . $results -> dep . " LIMIT 1") -> fetchField();
	$coordinator = db_query("SELECT {name} FROM {users} WHERE {uid}=" . $results -> coordinator . " LIMIT 1") -> fetchField();
	
	$teachers = "";
	$teacherx = explode(";", $results -> teacher);
	for ($i=1; $i < (count($teacherx) - 1); $i++) {
		$xx = db_query("SELECT * FROM {users} WHERE {uid}=" . $teacherx[$i] . " LIMIT 1") -> fetchObject();
		$teachers .= "\"" . $xx -> name . " / " . $xx -> mail . "\", ";
	}

	$prere = "";
	$results_prere = 0;
	if (is_numeric($results -> prere)) {
		$results_prere = $results -> prere;
	}
	$results_prere2 = 0;
	if (is_numeric($results -> prere2)) {
		$results_prere2 = $results -> prere2;
	}
	$results_prere3 = 0;
	if (is_numeric($results -> prere3)) {
		$results_prere3 = $results -> prere3;
	}
	$prere .= db_query("SELECT {name} FROM {syllabus_main_prerequisites} WHERE {id}=" . $results_prere . " LIMIT 1") -> fetchField() . " ,";
	$prere .= db_query("SELECT {name} FROM {syllabus_main_prerequisites} WHERE {id}=" . $results_prere2 . " LIMIT 1") -> fetchField() . " ,";
	$prere .= db_query("SELECT {name} FROM {syllabus_main_prerequisites} WHERE {id}=" . $results_prere3 . " LIMIT 1") -> fetchField() . " ,";

	$objectives = "";
	$objectivex = explode(";", $results -> teacher);
	for ($i=1; $i < (count($objectivex) - 1); $i++) {
		$xx = db_query("SELECT * FROM {syllabus_main_objective} WHERE {id}=" . $objectivex[$i] . " LIMIT 1") -> fetchObject();
		if (isset($xx -> name)) {
			$objectives .= "\"" . $xx -> name . "\", ";
		} else {
			$objectives .= "\"\", ";
		}
	}

	$knowledge = "";
	$w_outcome = explode(";", $results -> w_outcome);
	$w_assmeth = explode(";", $results -> w_assmeth);
	$w_code = explode(";", $results -> w_code);
	if (explode(";", $results -> w_outcome)) {
		for ($i=0; $i < (count($w_outcome) - 1); $i++) {
			if (empty($w_assmeth[$i])) {
				$w_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$w_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $w_assmeth[$i] . " LIMIT 1") -> fetchField();
			}
			if (empty($w_code[$i])) {
				$w_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$w_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=" . $w_code[$i] . " LIMIT 1") -> fetchField();
			}
			$knowledge .= "<tr>
							<td>W" . ($i + 1) . "</td>
							<td>" . (isset($w_outcome[$i]) ? $w_outcome[$i] : "") . "</td>
							<td>" . (isset($w_assmethx) ? $w_assmethx : "") . "</td>
							<td>" . (isset($w_codex) ? $w_codex : "") . "</td>
						</tr>";
		}
	}

	$skill = "";
	$u_outcome = explode(";", $results -> u_outcome);
	$u_assmeth = explode(";", $results -> u_assmeth);
	$u_code = explode(";", $results -> u_code);
	if (explode(";", $results -> u_outcome)) {
		for ($i=0; $i < (count($u_outcome) - 1); $i++) {
			if (empty($u_assmeth[$i])) {
				$u_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$u_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $u_assmeth[$i] . " LIMIT 1") -> fetchField();
			}
			if (empty($u_code[$i])) {
				$u_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$u_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=" . $u_code[$i] . " LIMIT 1") -> fetchField();
			}
			$skill .= "<tr>
							<td>U" . ($i + 1) . "</td>
							<td>" . (isset($u_outcome[$i]) ? $u_outcome[$i] : "") . "</td>
							<td>" . (isset($u_assmethx) ? $u_assmethx : "") . "</td>
							<td>" . (isset($u_codex) ? $u_codex : "") . "</td>
						</tr>";
		}
	}

	$social = "";
	$k_outcome = explode(";", $results -> k_outcome);
	$k_assmeth = explode(";", $results -> k_assmeth);
	$k_code = explode(";", $results -> k_code);
	if (explode(";", $results -> k_outcome)) {
		for ($i=0; $i < (count($k_outcome) - 1); $i++) {
			if (empty($k_assmeth[$i])) {
				$k_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$k_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $k_assmeth[$i] . " LIMIT 1") -> fetchField();
			}
			if (empty($k_code[$i])) {
				$k_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=0 LIMIT 1") -> fetchField();
			} else {
				$k_codex = db_query("SELECT {code} FROM {syllabus_main_code_desc} WHERE {id}=" . $k_code[$i] . " LIMIT 1") -> fetchField();
			}
			$social .= "<tr>
							<td>K" . ($i + 1) . "</td>
							<td>" . (isset($k_outcome[$i]) ? $k_outcome[$i] : "") . "</td>
							<td>" . (isset($k_assmethx) ? $k_assmethx : "") . "</td>
							<td>" . (isset($k_codex) ? $k_codex : "") . "</td>
						</tr>";
		}
	}

	$lecture = "";
	$lecturex = explode(";", $results -> lecture);
	for ($i=0; $i < (count($lecturex) - 1); $i++) {
		$lecture .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $lecturex[$i] . "</td>
					</tr>";
	}

	$lab = "";
	$labx = explode(";", $results -> lab);
	for ($i=0; $i < (count($labx) - 1); $i++) {
		$lab .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $labx[$i] . "</td>
					</tr>";
	}

	$discussion = "";
	$discussionx = explode(";", $results -> discussion);
	for ($i=0; $i < (count($discussionx) - 1); $i++) {
		$discussion .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $discussionx[$i] . "</td>
					</tr>";
	}

	$seminar = "";
	$seminarx = explode(";", $results -> seminar);
	for ($i=0; $i < (count($seminarx) - 1); $i++) {
		$seminar .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $seminarx[$i] . "</td>
					</tr>";
	}

	$workshop = "";
	$workshopx = explode(";", $results -> workshop);
	for ($i=0; $i < (count($workshopx) - 1); $i++) {
		$workshop .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $workshopx[$i] . "</td>
					</tr>";
	}

	$elearning = "";
	$elearningx = explode(";", $results -> elearning);
	for ($i=0; $i < (count($elearningx) - 1); $i++) {
		$elearning .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $elearningx[$i] . "</td>
					</tr>";
	}

	$lec_other = "";
	$lec_otherx = explode(";", $results -> lec_other);
	for ($i=0; $i < (count($lec_otherx) - 1); $i++) {
		$lec_other .= "<tr>
						<td>Topic " . ($i + 1) . "</td>
						<td>" . $lec_otherx[$i] . "</td>
					</tr>";
	}

	$assmeth = "";
	for ($i=0; $i < (count($w_assmeth) - 1); $i++) {
		$w_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $w_assmeth[$i] . " LIMIT 1") -> fetchField();
		$assmeth .= "\"" . $w_assmethx . "\", ";
	}
	for ($i=0; $i < (count($u_assmeth) - 1); $i++) {
		$u_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $u_assmeth[$i] . " LIMIT 1") -> fetchField();
		$assmeth .= "\"" . $u_assmethx . "\", ";
	}
	for ($i=0; $i < (count($k_assmeth) - 1); $i++) {
		$k_assmethx = db_query("SELECT {name} FROM {syllabus_main_assmeth} WHERE {id}=" . $k_assmeth[$i] . " LIMIT 1") -> fetchField();
		$assmeth .= "\"" . $k_assmethx . "\", ";
	}

	$percent = "";
	$percentx = explode(";", $results -> percent);
	for ($i=0; $i < (count($percentx) - 1); $i++) {
		$percent .= "\"" . ((isset($percentx[$i]) && $percentx[$i] != "") ? $percentx[$i] : "0") . "\", ";
	}

	$reading = "";
	$other = explode(";", $results -> other);
	$other_name = explode(";", $results -> other_name);
	for ($i=0; $i < (count($other) - 1); $i++) {
		$reading .= "<tr>
						<td>C." . ($i + 3) . "</td>
						<td>" . $other_name[$i] . "</td>
						<td>" . $other[$i] . "</td>
					</tr>";
	}

	$workload = "";
	$ws_hour = explode(";", $results -> ws_hour);
	$ws_hour2 = explode(";", $results -> ws_non_con_hour);
	$ws_activity = explode(";", $results -> ws_activity);
	for ($i=0; $i < (count($ws_hour) - 1); $i++) {
		if (empty($ws_activity[$i])) {
			$ws_activity[$i] = "";
		}
		$workload .= "<tr>
						<td></td>
						<td>" . $ws_activity[$i] . "</td>
						<td>" . $ws_hour[$i] . " h</td>
						<td>" . $ws_hour2[$i] . " h</td>
					</tr>";
	}

	$form["general_info_a"] = array(
		'#markup' => '<table class="table table-bordered table-hover">
		<tr>
			<th colspan="3"><h1>Course Syllabus: ' . $results -> name . '</h1></th>
		</tr>
		<tr>
			<th colspan = "3">A. Information on Subject Placement in Teaching Program Context</th>
		</tr>
		<tr>
			<td> A.1</td>
			<td>Course Code</td>
			<td>' . $results -> code . '</td>
		</tr>
		<tr>
			<td> A.2</td>
			<td>Academic Year</td>
			<td>' . $results -> year . '</td>
		</tr>
		<tr>
			<td> A.3</td>
			<td>Language of Instruction</td>
			<td>' . $results -> lang . '</td>
		</tr>
		<tr>
			<td> A.4</td>
			<td>Program coordinating the course</td>
			<td>' . $department . '</td>
		</tr>
		<tr>
			<td> A.5</td>
			<td>Program that taking the course</td>
			<td>' . $department . '</td>
		</tr>
		<tr>
			<td> A.6</td>
			<td>Study Profile</td>
			<td>' . $results -> degree . '</td>
		</tr>
		<tr>
			<td> A.7</td>
			<td>Mode of Study</td>
			<td>' . $results -> mode . '</td>
		</tr>
		<tr>
			<td> A.8</td>
			<td>Level of Study</td>
			<td>' . $results -> level . '</td>
		</tr>
	</table>'
	);
	$form["general_info_b"] = array(
		'#markup' => '<table class="table table-bordered table-hover">
   <tr>
      <th colspan="5"><label>B. Course overview (prerequisites, course objectives, learning outcomes, assessment methods, reference to field specific learning outcomes, course content)</label></th>
   </tr>
   <tr>
      <td> B.1</td>
      <td>Prerequisites</td>
      <td colspan="3">' . $prere . '</td>
   </tr>
   <tr>
      <td> B.2</td>
      <td>Course Objectives</td>
      <td colspan="3">' . $objectives . '</td>
   </tr>
   <tr>
      <td rowspan="3">B.3</td>
   </tr>
   <tr>
      <td>Code</td>
      <td>Learning Outcomes</b></td>
      <td>Assessment Methods (eg. midterm/final exam, written/oral exam, test, presentatin, term paper)</td>
      <td>Reference to field specific learning outcomes approved by the Senate</td>
   </tr>
   <tr>
    <td colspan="4">
      <div id="tabs">
        <ul>
          <li><a href="#knowledge">Knowledge</a></li>
          <li><a href="#skills">Skills</a></li>
          <li><a href="#social">Social Competences</a></li>
        </ul>
        <div id = "knowledge">
          <table class="table table-bordered table-hover">' . $knowledge . '</table>
        </div>
        <div id = "skills">
          <table class="table table-bordered table-hover">' . $skill . '</table>
        </div>
        <div id = "social">
          <table class="table table-bordered table-hover">' . $social . '</table>
        </div>
      </div>
      <script>
        $(function() {
           $(\'#tabs\').tabs();
        });
      </script>
    </td>
  </tr>
   <tr>
    <td>B.4</td>
    <td colspan="4">
      <div id="tabs2">
        <ul>
          <li><a href="#lectures">Lectures</a></li>
          <li><a href="#labs">Labs</a></li>
          <li><a href="#discussions">Discussions</a></li>
          <li><a href="#seminars">Seminars</a></li>
          <li><a href="#workshops">Workshops</a></li>
          <li><a href="#elearnings">E-learnings</a></li>
          <li><a href="#lec_other">Others</a></li>
        </ul>
        <div id = "lectures">
          <table class="table table-bordered table-hover">' . $lecture . '</table>
        </div>
        <div id = "labs">
          <table class="table table-bordered table-hover">' . $lab . '</table>
        </div>
        <div id = "discussions">
          <table class="table table-bordered table-hover">' . $discussion . '</table>
        </div>
        <div id = "seminars">
          <table class="table table-bordered table-hover">' . $seminar . '</table>
        </div>
        <div id = "workshops">
          <table class="table table-bordered table-hover">' . $workshop . '</table>
        </div>
        <div id = "elearnings">
          <table class="table table-bordered table-hover">' . $elearning . '</table>
        </div>
        <div id = "lec_other">
          <table class="table table-bordered table-hover">' . $lec_other . '</table>
        </div>
        <script>
          $(function() {
             $( \'#tabs2\' ).tabs();
          });
        </script>
    </td>
  </tr>
   <tr>
      <td rowspan="3">B.5</td>
      <td rowspan="2">Criteria for receiving credit for 
         the course
         (assessment methods)
      </td>
      <td colspan="2">Assessment Method</td>
      <td>Percentage</td>
   </tr>
   <tr>
      <td colspan="2">' . $assmeth . '</td>
			<td>' . $percent . '</td>
   </tr>
   <tr>
	  <td colspan = "4">Following percentages of marks meaning<br>
	  *&#09;0-49 -> 2 ----- Fail<br>
	  *&#09;50-59 -> 3 ---- Satisfactory<br>
	  *&#09;60-69 -> 3,5 -- Satisfactory Plus<br>
	  *&#09;70-79 -> 4 ---- Good<br>
	  *&#09;80-89 -> 4,5 -- Good Plus<br>
	  *&#09;90-100 -> 5 --- Very Good<br></td>
  </tr>
</table>'
	);
$form["general_info_c"] = array(
	'#markup' => '<table class="table table-bordered table-hover">
	<tr>
		<th colspan = "3">C. Readings</th>
	</tr>
		<tr>
			<td>C.1</td>
			<td>Compulsory readings</td>
			<td>' . $results -> compulsory . '</td>
		</tr>
		<tr>
			<td>C.2</td>
			<td>Supplementary readings</td>
			<td>' . $results -> supplementary . '</td>
		</tr>' . $reading . '</table>'
	);
$form["general_info_d"] = array(
	'#markup' => '<table class="table table-bordered table-hover">
	<tr>
		<th colspan = "4">D. Student workload</th>
	</tr>
	<tr>
		<td>D.1</td>
		<td colspan = "2">ECTS Credits</td>
		<td>' . $results -> ects . '</td>
	</tr>
	<tr>
		<td>D.2</td>
		<td colspan = "2">Workload(estimated number of hours )</td>
		<td>' . $results -> ects * 25 . '</td>
	</tr>
	<tr>
		<td>D.3</td>
		<td colspan = "2">Workload Structure</td>
		<td></td>
	</tr>
	<tr>
		<td></td>
		<td>Activity</td>
		<td>Contact Hour</td>
		<td>Non-Contact Hour</td>
	</tr>
	' . $workload . '</table>');
$form["general_info_e"] = array(
	'#markup' => '<table class="table table-bordered table-hover">
	<tr>
		<th colspan="3">E. Course coordinator, teacher(s), date of syllabus preparation</th>
	</tr>
	<tr>
		<td>E.1</td>
		<td> Course Coordinator</td>
		<td>' . $coordinator . '</td>
	</tr>
	<tr>
		<td>E.2</td>
		<td> Academic Teacher</td>
		<td>' . $teachers . '</td>
	</tr>
	<tr>
		<td>E.3</td>
		<td>Date of Preparation(latest submission date)</td>
		<td>' . $results -> pre_date . '</td>
	</tr>
</table>'
);

	return $form;
}