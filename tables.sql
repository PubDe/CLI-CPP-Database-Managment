--
-- Database: `school_database`
--


--
-- Table structure for table `course-table`
--

CREATE TABLE `course-table` (
  `course-code` int NOT NULL,
  `course-name` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;



--
-- Table structure for table `staff-table`
--

CREATE TABLE `staff-table` (
  `user_id` int NOT NULL,
  `name` varchar(45) NOT NULL,
  `email` varchar(25) NOT NULL,
  `post` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


--
-- Table structure for table `student-table`
--

CREATE TABLE `student-table` (
  `student-id` int NOT NULL,
  `student-name` varchar(45) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `email` varchar(25) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


--
-- Table structure for table `student&course`
--

CREATE TABLE `student&course` (
  `sid` int NOT NULL,
  `course-code` int NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


--
-- Table structure for table `user-table`
--

CREATE TABLE `user-table` (
  `user_id` int NOT NULL,
  `user_pin` int DEFAULT NULL,
  `user_type` char(1) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;


--
-- Indexes for dumped tables
--


--
-- Indexes for table `course-table`
--
ALTER TABLE `course-table`
  ADD PRIMARY KEY (`course-code`),
  ADD UNIQUE KEY `course_UNIQUE` (`course-name`),
  ADD UNIQUE KEY `course-code_UNIQUE` (`course-code`);



--
-- Indexes for table `staff-table`
--
ALTER TABLE `staff-table`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `sid_UNIQUE` (`user_id`);

--
-- Indexes for table `student-table`
--
ALTER TABLE `student-table`
  ADD PRIMARY KEY (`student-id`),
  ADD UNIQUE KEY `sid_UNIQUE` (`student-id`);

--
-- Indexes for table `student&course`
--
ALTER TABLE `student&course`
  ADD UNIQUE KEY `stid` (`sid`,`course-code`),
  ADD KEY `cocode` (`course-code`);

--
-- Indexes for table `user-table`
--
ALTER TABLE `user-table`
  ADD PRIMARY KEY (`user_id`),
  ADD UNIQUE KEY `userid_UNIQUE` (`user_id`);

--
-- Constraints for dumped tables
--

--
-- Constraints for table `staff-table`
--
ALTER TABLE `staff-table`
  ADD CONSTRAINT `staff_user` FOREIGN KEY (`user_id`) REFERENCES `user-table` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `student-table`
--
ALTER TABLE `student-table`
  ADD CONSTRAINT `studnt_user` FOREIGN KEY (`student-id`) REFERENCES `user-table` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `student&course`
--
ALTER TABLE `student&course`
  ADD CONSTRAINT `student&course_ibfk_1` FOREIGN KEY (`sid`) REFERENCES `student-table` (`student-id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `student&course_ibfk_2` FOREIGN KEY (`course-code`) REFERENCES `course-table` (`course-code`) ON DELETE CASCADE ON UPDATE CASCADE;
COMMIT;

