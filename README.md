# Pawche

## Oracle connection

The app connects through the `Source_Projet2A` ODBC DSN using the `PAWCHE_2`
account. The password (`1234`) is set in `connection.cpp`, as in the example
connection code. Update those values to match your local Oracle configuration.
If `sqlnet.ora` is present beside the application, the app sets `TNS_ADMIN` to
that directory before initializing the ODBC connection.

The supplied SQL export starts with `DROP TABLE` statements. Do not run it
unchanged against a database containing data.