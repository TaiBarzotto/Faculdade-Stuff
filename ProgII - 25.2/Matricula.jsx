import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Matricula() {
  const [matriculas, setMatriculas] = useState([]);
  const [novoMatriculaIdAluno, setNovoMatriculaIdAluno] = useState("");
  const [novoMatriculaIdCurso, setNovoMatriculaIdCurso] = useState("");


  const buscaMatriculas = async () => {
    try {
      const response = await axios.get("http://localhost:3002/matricula/");
      console.log(response.data);
      setMatriculas(response.data.matriculas);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaMatriculas();
    },
    []
  )

  const cadastrarMatricula = async () => {
    const response = await axios.post("http://localhost:3002/matricula", {
      id_aluno: novoMatriculaIdAluno,
      id_curso: novoMatriculaIdCurso
    });
    console.log(response.data)
  }


  return (<>
    <ul>
      {matriculas.map((matricula) => {
        return <li key={matricula.id_aluno}>{matricula.Aluno.nome} - {matricula.Curso.descricao}</li>;
      })}
    </ul>
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Id do aluno: </label>
        <input type="text" value={novoMatriculaIdAluno} onChange={(event) => setNovoMatriculaIdAluno(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Id do Curso: </label>
        <input type="text" value={novoMatriculaIdCurso} onChange={(event) => setNovoMatriculaIdCurso(event.target.value)} />
      </Stack>
      <button onClick={cadastrarMatricula} type="submit">Cadastrar Matricula</button>
    </Stack>
  </>)

}
