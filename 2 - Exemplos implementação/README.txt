Para compilar cada exemplo, entrar na pasta do exemplo e então criar diretório build,
e executar os seguintes comandos dentro do diretório:

cmake -DCMAKE_BUILD_TYPE=Release ..
make -j <numero_nucleos_cpu>
./<nome_do_executavel_gerado>
