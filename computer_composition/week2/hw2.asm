# week2 mips作业

# 主存中的数据
.data
	word: .space 50
	success_message: .ascii "Success! Location: \0"
	fail_message: .ascii "Fail\0"
	line_break: .ascii "\n\0"

# 代码段
.text


main:
	#读入字符串，并把其地址存入寄存器s0,长度存入s1
	la $a0,word
	li $a1,50
	li $v0,8
	syscall
	move $s0,$a0
	move $s1,$a1
	j loop_read

loop_read:
	#读入待查找的字符,将其ascii码存入s2
	li $v0,12
	syscall
	move $s2,$v0
	#判断是否为？，如果不是？，跳转至查询
	#反之，结束
	li $t0 63
	bne $t0,$s2,is_find

	li $v0,10
	syscall
	
	
is_find:
	#断句
	li $v0,4
	la $a0,line_break
	syscall
	# 开始循环
	# 初始化	
	li $s7,0
	j find_loop

find_loop:
	# 循环，并查找
	# s7 存储当前比较字符的位置，
	# t1 存储当前比较的字符地址，s0是字符串地址
	add $t1,$s0,$s7
	# t0 存储当前比较的字符， 与目标字符s2进行比较
	lb $t0,($t1)
	# 如果没有 \0，进行查找
	bne $t0,0,is_search
	j is_fail

# 循环查询
is_search:
	add $s7,$s7,1
	beq $s2,$t0,is_success
	j find_loop


# 查找成功
is_success:
	# 输出成功的结果，s7存储了字符的位置
	li $v0,4
	la $a0,success_message
	syscall
	
	li $v0,1
	move $a0,$s7
	syscall
	
	li $v0,4
	la $a0,line_break
	syscall

	# 跳转至 读取下一次的字符
	j loop_read
	
	
is_fail:
	# 输出失败的结果
	li $v0,4
	la $a0,fail_message
	syscall
	
	li $v0,4
	la $a0,line_break
	syscall
	# 跳转至 读取下一次的字符
	j loop_read
