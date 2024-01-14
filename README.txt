Durante la realizzazione del progetto, sono stati presi in considerazione i principali aspetti della programmazione ad oggetti.

Ogni classe è stata progettata per svolgere una singola funzione e mantenere una sola responsabilità.

L'architettura segue i migliori design pattern, inclusa un'implementazione di base del pattern di dependency injection. Ciò permette di semplificare il codice e mostrare le potenzialità della gestione dinamica della memoria in C++.

Per rendere il progetto più interessante, è stata adottata un'architettura simile a quella di un servizio web. Sono state nettamente separate le parti del server (chiamato "engine" nel nostro caso) e del client.

Per quanto riguarda l'ereditarietà, è stata mantenuta al minimo, poiché non è strettamente necessaria per il metodo risolutivo adottato. Tuttavia, sono presenti esempi di ereditarietà di interfacce.

La gestione degli errori è stata semplificata grazie all'uso della monade Result<T>. Le eccezioni vengono raccolte a livello di GameContext e restituite al client come un Result<T> contenente un errore.