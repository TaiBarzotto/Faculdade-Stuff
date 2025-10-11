const express = require("express");
const professorService = require("../services/professor-service");

const professorRouter = express.Router();

// POST /professor - Criar novo professor
professorRouter.post("/", professorService.criaProfessor);

// GET /professores - Retornar todos os professores
professorRouter.get("/todos", professorService.retornaTodosProfessores);

// GET /professor/:id - Retornar professor por ID
professorRouter.get("/:id", professorService.retornaProfessorPorId);

// PUT /professor/:id - Atualizar professor
professorRouter.put("/:id", professorService.atualizaProfessor);

// DELETE /professor/:id - Deletar professor
professorRouter.delete("/:id", professorService.deletaProfessor);

module.exports = professorRouter;
