DROP TABLE IF EXISTS fs_handler_invocation;
DROP TABLE IF EXISTS fs_session;

CREATE TABLE fs_session
( id                    INTEGER         UNSIGNED    NOT NULL    AUTO_INCREMENT  PRIMARY KEY
, token                 VARCHAR(32)     NOT NULL
, created_by            INTEGER         UNSIGNED    NOT NULL    DEFAULT 0
, create_date           DATETIME        NOT NULL
, active_flag           TINYINT         NOT NULL    DEFAULT 1
, last_refreshed_date   DATETIME
, duration_minutes      INTEGER         UNSIGNED    DEFAULT 120
, server_host           VARCHAR(64)
, server_port           VARCHAR(64)
, client_ip_address     VARCHAR(64)
) Engine=InnoDB;

create table fs_handler_invocation
( id                    INTEGER         UNSIGNED    NOT NULL    AUTO_INCREMENT  PRIMARY KEY
, fs_session_id         INTEGER         UNSIGNED    NOT NULL
, handler               VARCHAR(32)     NOT NULL
, invocation_start_date DATETIME        NOT NULL
, invocation_end_date   DATETIME
, fault_string          TEXT
, server_host           VARCHAR(64)
, server_port           VARCHAR(64)
, CONSTRAINT FOREIGN KEY( fs_session_id ) REFERENCES fs_session( id )
) Engine=InnoDB;

#grant all on fs.* to 'feynman'@'localhost' identified by 'feynman';
