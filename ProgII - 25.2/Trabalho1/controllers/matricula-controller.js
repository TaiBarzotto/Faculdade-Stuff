const express = require("express");
const matriculaService = require("../services/matricula-service");

const matriculaRouter = express.Router();

// POST /matricula - Criar nova matricula
matriculaRouter.post("/", matriculaService.criaMatricula);

// GET /matriculas - Retornar todas as matriculas
matriculaRouter.get("/", matriculaService.retornaTodasMatriculas);

// GET /matricula/:id_aluno - Retornar todas as matriculas do aluno
matriculaRouter.get("/aluno/:id_aluno", matriculaService.retornaMatriculaAluno);

// GET /matricula/:id_curso - Retornar todas as matriculas do curso
matriculaRouter.get("/curso/:id_curso", matriculaService.retornaTodasMatriculasCurso);

// PUT /matricula/:id_aluno - Atualizar matricula
matriculaRouter.put("/:id_aluno", matriculaService.atualizaMatricula);

// DELETE /matricula/:id_aluno - Deletar matricula
matriculaRouter.delete("/:id_aluno", matriculaService.deletaMatricula);

module.exports = matriculaRouter;