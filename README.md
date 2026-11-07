# Pawche

## Oracle connection

The app connects to Oracle using the `PAWCHE_2` account by default and the
`Source_Projet2A` ODBC DSN. It first checks the Windows Credential Manager for
a saved password. If none is available, the app asks for it in a masked dialog
at startup and saves it securely after a successful login. Alternatively, set
`PAWCHE_DB_PASSWORD` before launching to use an environment-provided password:
if a saved password is rejected, the app prompts for a replacement and saves
it only after a successful login.

```powershell
$env:PAWCHE_DB_PASSWORD = "your Oracle password"
```

The `Source_Projet2A` User DSN on this machine targets Oracle XE and is the
selected DSN (Windows prefers a User DSN over a same-named System DSN). It must
point to the Oracle service containing the `PAWCHE_2` schema from `export.sql`.
Connect as `PAWCHE_2` (or set `PAWCHE_DB_USER` to the schema owner) and import
the export into that schema before launching the app. The app does not run the
export automatically. The export begins with `DROP TABLE` statements, so
review it and back up any existing data before running it in SQL Developer.
Its tables include `ANIMAUX`, `STOCKS`, `COMMANDE`, `DETAILACHAT`, `DETAILVENTE`,
`GESTIONRENDEZVOUS`, and `EMPLOYÉ`.

Override the DSN or username if your local settings differ:

```powershell
$env:PAWCHE_ODBC_DSN = "your ODBC DSN"
$env:PAWCHE_DB_USER = "PAWCHE_2"
```

The supplied SQL export starts with `DROP TABLE` statements. Do not run it
unchanged against a database containing data.