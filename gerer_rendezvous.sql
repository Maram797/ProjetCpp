
CREATE OR REPLACE PROCEDURE ASSURER_ANIMAL (
    p_nom        IN ANIMAUX.NOM%TYPE,
    p_telephone  IN ANIMAUX.TELEPHONE%TYPE
) AS
    v_id_animal ANIMAUX.ID_ANIMAL%TYPE;
BEGIN
    BEGIN
        SELECT ID_ANIMAL
          INTO v_id_animal
          FROM ANIMAUX
         WHERE LOWER(NOM) = LOWER(TRIM(p_nom))
           AND TELEPHONE = p_telephone;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            LOCK TABLE ANIMAUX IN EXCLUSIVE MODE;
            BEGIN
                SELECT ID_ANIMAL
                  INTO v_id_animal
                  FROM ANIMAUX
                 WHERE LOWER(NOM) = LOWER(TRIM(p_nom))
                   AND TELEPHONE = p_telephone;
            EXCEPTION
                WHEN NO_DATA_FOUND THEN
                    SELECT NVL(MAX(ID_ANIMAL), 0) + 1
                      INTO v_id_animal
                      FROM ANIMAUX;

                    INSERT INTO ANIMAUX (ID_ANIMAL, NOM, NOM_PROPRIETAIRE, TELEPHONE)
                    VALUES (v_id_animal, TRIM(p_nom), UNISTR('Non renseign\00E9'), p_telephone);
                WHEN TOO_MANY_ROWS THEN
                    RAISE_APPLICATION_ERROR(-20001, 'Plusieurs animaux correspondent au même nom et téléphone.');
            END;
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'Plusieurs animaux correspondent au même nom et téléphone.');
    END;
END;
/

CREATE OR REPLACE PROCEDURE ENREGISTRER_RENDEZVOUS (
    p_nom       IN ANIMAUX.NOM%TYPE,
    p_telephone IN ANIMAUX.TELEPHONE%TYPE,
    p_heure     IN GESTIONRENDEZVOUS.HEURE%TYPE,
    p_etat      IN GESTIONRENDEZVOUS.ETAT%TYPE,
    p_date      IN GESTIONRENDEZVOUS.DATE_RENDEZ_VOUS%TYPE,
    p_motif     IN GESTIONRENDEZVOUS.MOTIF%TYPE
) AS
    v_id_animal ANIMAUX.ID_ANIMAL%TYPE;
    v_proprietaire ANIMAUX.NOM_PROPRIETAIRE%TYPE;
BEGIN
    ASSURER_ANIMAL(p_nom, p_telephone);

    SELECT ID_ANIMAL, NOM_PROPRIETAIRE
      INTO v_id_animal, v_proprietaire
      FROM ANIMAUX
     WHERE LOWER(NOM) = LOWER(TRIM(p_nom))
       AND TELEPHONE = p_telephone;

    INSERT INTO GESTIONRENDEZVOUS
        (ID_ANIMAL, HEURE, ETAT, TELEPHONE, DATE_RENDEZ_VOUS, MOTIF, PROPRIETAIRE)
    VALUES
        (v_id_animal, p_heure, p_etat, p_telephone, p_date, p_motif, v_proprietaire);
END;
/

CREATE OR REPLACE PROCEDURE MODIFIER_RENDEZVOUS (
    p_id_animal          IN GESTIONRENDEZVOUS.ID_ANIMAL%TYPE,
    p_ancien_telephone   IN GESTIONRENDEZVOUS.TELEPHONE%TYPE,
    p_nom                IN ANIMAUX.NOM%TYPE,
    p_nouveau_telephone  IN ANIMAUX.TELEPHONE%TYPE,
    p_heure              IN GESTIONRENDEZVOUS.HEURE%TYPE,
    p_etat               IN GESTIONRENDEZVOUS.ETAT%TYPE,
    p_date               IN GESTIONRENDEZVOUS.DATE_RENDEZ_VOUS%TYPE,
    p_motif              IN GESTIONRENDEZVOUS.MOTIF%TYPE,
    p_proprietaire       IN GESTIONRENDEZVOUS.PROPRIETAIRE%TYPE
) AS
BEGIN
    UPDATE ANIMAUX
       SET NOM = p_nom, TELEPHONE = p_nouveau_telephone
     WHERE ID_ANIMAL = p_id_animal;
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20002, 'L''animal associé n''existe plus dans la base de données.');
    END IF;

    UPDATE GESTIONRENDEZVOUS
       SET HEURE = p_heure, ETAT = p_etat, TELEPHONE = p_nouveau_telephone,
           DATE_RENDEZ_VOUS = p_date, MOTIF = p_motif, PROPRIETAIRE = p_proprietaire
     WHERE ID_ANIMAL = p_id_animal
       AND TELEPHONE = p_ancien_telephone;
    IF SQL%ROWCOUNT = 0 THEN
        RAISE_APPLICATION_ERROR(-20003, 'Le rendez-vous n''existe plus dans la base de données.');
    END IF;
END;
/