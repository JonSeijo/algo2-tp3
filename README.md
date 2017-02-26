# algo2-tp3
TP3 Implementacion.

Archivos en la carpeta "Base" (puede cambiarse)

# IMPORTANTE NOTA POST CUATRI:

En los ultimos dias antes de la entrega tuvimos un pico de commits y branches desesperados, un test de la catedra nos fallaba y no podiamos encontrar el error. Termino siendo un problema del bot de la catedra, que pudimos resorverlo en los labos del dc con nuestro ayudante corrector. 

Por este motivo, no garantizo que el repo en su version actual sea la version que fue entregada, sobre todo en el CasoMov1. Ni siquiera garantizo que compile (aunque deberia)

Espero que te sirva para algo (budum tss)


---------------

# Como hacer un rebase

http://stackoverflow.com/questions/5601931/best-and-safest-way-to-merge-a-git-branch-into-master


```
git checkout master
git pull
git checkout NombreDelBranch
git pull
git rebase -i master
git checkout master
git merge NombreDelBranch
```

# Como se compila (en teoria)

*desde la carpeta "Base"*

##### para el test general:
 `make`

 `make valgrind`

##### para el test de Mapa:
 `make test_mapa`
##### para valgrind de Mapa:
 `make val_mapa`

##### para el test de ColaPrioridad:
 `make test_cola`
##### para valgrind de ColaPrioridad:
 `make val_cola`

##### para el test de DiccString:
 `make test_dicc`
##### para valgrind de DiccString:
 `make val_dicc`

##### para borrar:
 `make clean`


