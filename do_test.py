import subprocess

for i in range(1, 4):
	for t in range(1, 4):	

		dados = '' 
		media_deadline = 0.
		media_contexto = 0.
	
		for x in range(0, 30):

			deadline = subprocess.Popen('./simulador '+ str(i) +' tests/test_'+ str(t) +' output  | grep -o Cumpriu | wc -l', shell=True, stdout=subprocess.PIPE).stdout.read()
			contexto = subprocess.Popen('tail -n 1 output', shell=True, stdout=subprocess.PIPE).stdout.read()		

			media_deadline += float(deadline.rstrip())
			media_contexto += float(contexto.rstrip())
			dados += '%s,%s\n' % (deadline.rstrip(), contexto.rstrip())

		dados += '%s,%s\n' % (media_deadline / 30, media_contexto / 30)
		test_file = 'result_escalonador_%s_test_%s.txt' % (i, t)

		with open(test_file, 'w') as result:
			result.write(dados)

