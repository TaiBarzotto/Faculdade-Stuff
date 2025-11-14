import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Curso() {
  const [cursos, setCursos] = useState([]);
  const [novoCurso, setNovoCurso] = useState("");
  const [idCurso, setIdCurso] = useState("");

  const buscaCursos = async () => {
    try {
      const response = await axios.get("http://localhost:3002/curso/todos");
      console.log(response.data);
      setCursos(response.data.curso);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaCursos();
    },
    []
  )

  const cadastrarCurso = async () => {
    const response = await axios.post("http://localhost:3002/curso", {
      descricao: novoCurso
    });
    console.log(response.data)
  }

  const deletaCurso = async () => {
    const response = await axios.delete("http://localhost:3002/curso", {
      id: idCurso
    });
    console.log(response.data)
  }

  const atualizaCurso = async () => {
    const response = await axios.put("http://localhost:3002/curso", {
      descricao: novoCurso
    });
    console.log(response.data)
  }

  return (<>
    <ul>
      {cursos.map((curso) => {
        return <li key={curso.id}>{curso.descricao}</li>;
      })}
    </ul>
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do curso: </label>
        <input type="text" value={novoCurso} onChange={(event) => {setNovoCurso(event.target.value); setIdCurso(key)}} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarCurso} type="submit">Cadastrar Curso</button>
        <button onClick={atualizaCurso} type="submit">Atualiza Curso</button>
      </Stack>
    </Stack>
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Id do curso: </label>
        <input type="text" value={idCurso} onChange={(event) => setIdCurso(event.target.value)} />
      </Stack>
      <button onClick={deletaCurso} type="submit">Deleta Curso</button>
    </Stack>
  </>)

}
