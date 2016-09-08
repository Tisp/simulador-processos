import subprocess

for i in range(1, 4):

	dados = '' 
	media_deadline = 0.
	media_contexto = 0.

	for x in range(0, 1):
		deadline = subprocess.Popen('./simulador '+ str(i) +' tests/test_1 output  | grep -o Cumpriu | wc -l', shell=True, stdout=subprocess.PIPE).stdout.read()
		contexto = subprocess.Popen('tail -n 1 output', shell=True, stdout=subprocess.PIPE).stdout.read()		

		media_deadline += float(deadline)
		media_contexto += float(contexto)
		dados += '%s %s\n' % (deadline.rstrip(), contexto.rstrip())

	dados += '%s %s\n' % (media_deadline / 30, media_contexto / 30)

	test_file = 'test_result_%s.txt' % (i)

	with open(test_file, 'w') as result:
		result.write(dados)

