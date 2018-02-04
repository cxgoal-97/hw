.data
# 数字的字符数组以及数字对应的偏移量
array_num_word: .ascii
  "zero\0","First\0","Second\0","Third\0","Fourth\0",
  "Firth\0","Sixth\0","Seventh\0","Eighth\0","Ninth\0"

array_num_offset: .word
   0,5,11,18,24,
   31,37,45,52,58

# 字母对应的字符数组以及数字对应的偏移量
# 此外，由于大小写字母结果的区别仅仅与第一个字符有关
# 故将大小写看成一样的情形

array_letter_word: .ascii
  "lpha\0","ravo\0","hina\0","elta\0","cho\0","oxtrot\0",
  "olf\0","otel\0","ndia\0","uliet\0","ilo\0","ima\0",
  "ary\0","ovember\0","scar\0","aper\0","uebec\0","esearch\0",
  "lerra\0","ango\0","niform\0","ictor\0","hisky\0","-ray\0",
  "ankee\0","ulu\0"

array_letter_offset: .word
   0,5,10,15,20,24,
   31,35,40,45,51,55,
   59,63,71,76,81,87,
   95,101,106,113,119,125,
   130,136

.text

	#将数字对应的字符数组存入寄存器s0,偏移量存入s1
	la $s0, array_num_word
	la $s1, array_num_offset

	#将字母对应的字符数组存入寄存器s2,偏移量存入s2
	la $s2, array_letter_word
	la $s3, array_letter_offset




main:
	# 读入字符，存入寄存器v0
	li $v0, 12
	syscall

	# 判断是否为大写字母
	li $t0,64
	li $t1,91
	#判断是否大于65,1为真
	slt $t0,$t0,$v0
	#判断是否小于90,1为真
	slt $t1,$v0,$t1
	beq $t1,$t0,isUpLetter

	# 判断是否为小写字母
	li $t0,96 
	li $t1,123
	#判断是否大于97
	slt $t0,$t0,$v0
	#判断是否小于122
	slt $t1,$v0,$t1
	beq $t0,$t1,isLowerLetter

	# 判断是否为数字
	li $t0,47
	li $t1,58
	#判断是否大于48,1代表真
	slt $t0,$t0,$v0
	#判断是否小与57,1代表真
	slt $t1,$v0,$t1
	beq $t1,$t0,isNum

	# 判断是否为?,63
	li $t0,63
	beq $v0,$t0,isEnd

	# 这是其他情况
	li $v0,11
	li $a0,42
	syscall

# 循环读入
j main



isNum:
# v0 存放的是数字的ascci吗
# 先转换
	li $t0 48
	sub $v0,$v0,$t0
	li $t0 4
	mult $t0,$v0
	mflo $t0
# 获得偏移量
	add $t0,$t0,$s1
	lw $t0,($t0)

# 获得地址
# move $a0,$t0
# li $v0,1
# syscall

	add $t0,$t0,$s0

	li $v0,4
	la $a0,($t0)
	syscall
	j main

isUpLetter:
#输出第一个字符
	move $a0, $v0
	move $t1, $v0 
	li $v0, 11
	syscall

# t1 存放的是大写字母的ascci吗
# 先转换
	li $t0 65
	sub $t1,$t1,$t0
	li $t0 4
	mult $t0,$t1
	mflo $t0
# 获得偏移量
	add $t0,$t0,$s3
	lw $t0,($t0)

# 获得地址
# move $a0,$t0
# li $v0,1
# syscall
	add $t0,$t0,$s2
	li $v0,4
	la $a0,($t0)
	syscall
	j main

isLowerLetter:
#输出第一个字符
	move $t1, $v0
	move $a0, $v0
	li $v0, 11
	syscall

# t1 存放的是小写字母的ascci吗
# 先转换
	li $t0 97
	sub $t1,$t1,$t0
	li $t0 4
	mult $t0,$t1
	mflo $t0
# 获得偏移量
	add $t0,$t0,$s3
	lw $t0,($t0)

# 获得地址
# move $a0,$t0
# li $v0,1
# syscall
	add $t0,$t0,$s2

	li $v0,4
	la $a0,($t0)
	syscall
	j main

isEnd:
#退出程序
	li $v0, 10
	syscall

#la $a0, 2($s3)
#li $v0, 4
#syscall

#la $a0, 12($s3)
#li $v0, 4
#syscall 
