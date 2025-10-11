CREATE TABLE aluno
(
  id bigint  NOT NULL,
  nome      varchar NOT NULL,
  email     varchar NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE curso
(
  id bigint  NOT NULL,
  descricao varchar NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE matricula
(
  id_aluno bigint  NOT NULL,
  id_curso bigint NOT NULL,
  PRIMARY KEY (id_aluno, id_curso),
  CONSTRAINT FK_matricula_aluno
    FOREIGN KEY (id_aluno)
    REFERENCES aluno (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT FK_matricula_curso
    FOREIGN KEY (id_curso)
    REFERENCES curso (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);

-- ===== DADOS DE EXEMPLO =====
INSERT INTO aluno (id, nome, email) VALUES (1, 'Huguinho Pato', 'huguinho.pato@estudante.uffs.edu.br');
INSERT INTO aluno (id, nome, email) VALUES (2, 'Zézinho Pato', 'zezinho.pato@estudante.uffs.edu.br');
INSERT INTO aluno (id, nome, email) VALUES (3, 'Luizinho Pato', 'luizinho.pato@estudante.uffs.edu.br');

INSERT INTO curso (id, descricao) VALUES (1, 'Engenharia de Software');
INSERT INTO curso (id, descricao) VALUES (2, 'Sistemas de Informação');
INSERT INTO curso (id, descricao) VALUES (3, 'Ciência da Computação');

INSERT INTO matricula (id_aluno, id_curso) VALUES (1, 1);
INSERT INTO matricula (id_aluno, id_curso) VALUES (2, 2);
INSERT INTO matricula (id_aluno, id_curso) VALUES (3, 3);

-- ===== DADOS DE EXEMPLO =====
CREATE TABLE professor
(
  id bigint  NOT NULL,
  nome      varchar NOT NULL,
  email     varchar NOT NULL,
  PRIMARY KEY (id)
);



CREATE TABLE ccr
(
  id        BIGINT  NOT NULL,
  descricao VARCHAR NULL    ,
  ementa    VARCHAR NULL    ,
  id_curso  int     NOT NULL,
  PRIMARY KEY (id),
  CONSTRAINT FK_ccr_curso
    FOREIGN KEY (id_curso)
    REFERENCES curso (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);

CREATE TABLE professor_ccr
(
  id_professor bigint  NOT NULL,
  id_ccr bigint NOT NULL,
  PRIMARY KEY (id_professor, id_ccr),
    CONSTRAINT FK_professor_ccr_professor
    FOREIGN KEY (id_professor)
    REFERENCES professor (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
    CONSTRAINT FK_professor_ccr_ccr
    FOREIGN KEY (id_ccr)
    REFERENCES ccr (id)
    ON DELETE CASCADE
    ON UPDATE CASCADE
);

INSERT INTO professor (id, nome, email) VALUES (1, 'Giancarlo Salton', 'gian@uffs.edu.br');
INSERT INTO professor (id, nome, email) VALUES (2, 'Luciano Caimi', 'lcaimi@uffs.edu.br');


INSERT INTO ccr (id, descricao, ementa, id_curso) VALUES (1, 'Prog II', 'Programação Web; HTML, CSS, JavaScript; Node.js; Express.', 3);
INSERT INTO ccr (id, descricao, ementa, id_curso) VALUES (2, 'Organização de Computadores', 'Organização de Computadores; Arquitetura de Computadores; Sistemas Operacionais; Redes de Computadores', 3);

INSERT INTO professor_ccr (id_professor, id_ccr) VALUES (1, 1);
INSERT INTO professor_ccr (id_professor, id_ccr) VALUES (2, 2);
