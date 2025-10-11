const express = require("express");
const cursoService = require("../services/curso-service");

const cursoRouter = express.Router();

// POST /curso - Criar novo curso
cursoRouter.post("/", cursoService.criaCurso);

// GET /cursos - Retornar todos os cursos
cursoRouter.get("/todos", cursoService.retornaTodosCursos);

// GET /curso/:id - Retornar curso por ID
cursoRouter.get("/:id", cursoService.retornaCursoPorId);

// PUT /curso/:id - Atualizar curso
cursoRouter.put("/:id", cursoService.atualizaCurso);

// DELETE /curso/:id - Deletar curso
cursoRouter.delete("/:id", cursoService.deletaCurso);

module.exports = cursoRouter;
