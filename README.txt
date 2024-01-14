Nella realizzazione del progetto sono stati tenuti bene a mente i più importanti aspetti della programmazione ad oggetti.

Ogni classe infatti è stata resa tale per cui vada a ricoprire una ed una sola funzione, mantenendo una ed una sola responsabilità.

L'architettura segue i miglior design pattern, tra i quali un'implementazione molto basilare del pattern di dependency injection. Questo per snellire il codice, nonché mostrare le potenzialità della gestione dinamica della memoria in C++.

Per rendere più interessante il progetto si è inoltre scelto di adottare un'architettura simile a quella che si avrebbe per un servizio web. Infatti si è diviso nettamente quello che sarebbe il server, ossia l'engine secondo la nomenclatura da noi adottata, con quello che è il client.

Per quanto concerne l'ereditarietà, si è preferito tenerla al minimo in quanto non esattamente funzionale al metodo risolutivo adottato. Non mancano però esempi di ereditarietà di interfaccie.

La gestione inoltre degli errori è stata resa facile dall'uso della monade Result<T>. Infatti le eccezioni vengono raccolte a livello di GameContext, ritornando così al client un Result<T> contenente un errore.