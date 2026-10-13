-- ============================================================
-- Projet : Gestion des rendez-vous
-- Creation de la table GESTIONRENDEZVOUS (meme structure que
-- la table existante : HEURE, ETAT, TELEPHONE, DATE_RENDEZ_VOUS, MOTIF)
--
-- A executer connecte avec l'utilisateur de connection.cpp.
--
-- Pour recommencer a zero, decommentez cette ligne :
-- DROP TABLE gestionrendezvous;
-- ============================================================

-- 1) Table
CREATE TABLE gestionrendezvous (
    heure             TIMESTAMP          NOT NULL,
    etat              NVARCHAR2(50),
    telephone         NUMBER             NOT NULL,
    date_rendez_vous  DATE               NOT NULL,
    motif             VARCHAR2(200)
);

-- 2) Test rapide
INSERT INTO gestionrendezvous (heure, etat, telephone, date_rendez_vous, motif)
VALUES (TO_TIMESTAMP('09:00', 'HH24:MI'), 'En attente', 12345678, TRUNC(SYSDATE), 'Consultation');
COMMIT;

SELECT * FROM gestionrendezvous;