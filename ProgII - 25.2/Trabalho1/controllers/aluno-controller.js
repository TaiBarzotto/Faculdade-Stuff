const express = require("express");
const alunoService = require("../services/aluno-service");

const alunoRouter = express.Router();

// POST /aluno - Criar novo aluno
alunoRouter.post("/", alunoService.criaAluno);

// GET /alunos - Retornar todos os alunos
alunoRouter.get("/todos", alunoService.retornaTodosAlunos);

// GET /aluno/:id - Retornar aluno por ID
alunoRouter.get("/:id", alunoService.retornaAlunoPorId);

// PUT /aluno/:id - Atualizar aluno
alunoRouter.put("/:id", alunoService.atualizaAluno);

// DELETE /aluno/:id - Deletar aluno
alunoRouter.delete("/:id", alunoService.deletaAluno);

module.exports = alunoRouter;
