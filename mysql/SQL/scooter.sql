SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for scooter
-- ----------------------------
DROP TABLE IF EXISTS `scooter`;
CREATE TABLE `scooter` (
  `id` varchar(32) NOT NULL,
  `m_prot_head1` varchar(8) DEFAULT NULL,
  `m_prot_head2` varchar(8) DEFAULT NULL,
  `m_bootloader_mode` varchar(40) DEFAULT NULL,
  `m_aes_key` varchar(128) DEFAULT NULL COMMENT '两次加密后的值',
  `m_random_array` varchar(96) DEFAULT NULL COMMENT '数据指纹随机码：96Bytes',
  `m_result` varchar(128) DEFAULT NULL COMMENT '结果：96Bytes',
  `create_time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;