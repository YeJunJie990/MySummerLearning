#!/bin/bash

mysql -u root;
use yejjbase;
CREATE TABLE `student_info` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT COMMENT 'id，主键',
  `student_name` varchar(50) COMMENT '学生姓名',
  `student_age` int COMMENT '学生年龄',
  `student_sex` varchar(10) COMMENT '学生性别',
  PRIMARY KEY (`id`)
);

INSERT INTO `student_info`
(`student_name`, `student_age`,`student_sex`)
VALUES
('葛尧', 17 , '男');

INSERT INTO `student_info`
(`student_name`, `student_age`,`student_sex`)
VALUES
('XH', 23 , '男');

INSERT INTO `student_info`
(`student_name`, `student_age`,`student_sex`)
VALUES
('QHR', 24 , '男');

INSERT INTO `student_info`
(`student_name`, `student_age`,`student_sex`)
VALUES
('WR', 22 , '女');

exit