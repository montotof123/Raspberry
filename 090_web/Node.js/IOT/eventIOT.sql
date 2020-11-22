-- Table: raspberry."eventIOT"

-- DROP TABLE raspberry."eventIOT";

CREATE TABLE raspberry."eventIOT"
(
    horaire timestamp with time zone NOT NULL,
    id character varying(50) COLLATE pg_catalog."default" NOT NULL,
    CONSTRAINT "eventIOT_pkey" PRIMARY KEY (horaire, id)
)
WITH (
    OIDS = FALSE
)
TABLESPACE pg_default;

ALTER TABLE raspberry."eventIOT"
    OWNER to postgres;
COMMENT ON TABLE raspberry."eventIOT"
    IS 'Mémorisation des évènements des objets connectés';