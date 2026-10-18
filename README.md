# Pawche

## Oracle connection

The app connects to Oracle using the `elyes` account by default and the
`Source_Projet2A` ODBC DSN. If `PAWCHE_DB_PASSWORD` is not set, the app asks
for the password in a masked dialog at startup. Alternatively, set it before
launching:

```powershell
$env:PAWCHE_DB_PASSWORD = "your Oracle password"
```

SQL Developer must connect to the same database service as the `elyes` account
to show the app's schema. The exported tables have been created in `ELYES`
without dropping existing tables or importing the export's sample rows. The
schema contains `ANIMAUX`, `STOCKS`, `COMMANDE`, `DETAILACHAT`, `DETAILVENTE`,
`GESTIONRENDEZVOUS`, and `EMPLOYÉ`.

Override the DSN or username if your local settings differ:

```powershell
$env:PAWCHE_ODBC_DSN = "your ODBC DSN"
$env:PAWCHE_DB_USER = "elyes"
```

The supplied SQL export starts with `DROP TABLE` statements. Do not run it
unchanged against a database containing data.