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
    try{
      const response = await axios.post("http://localhost:3002/curso", {
        descricao: novoCurso
      });
      buscaCursos();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  const deletaCurso = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/curso/${id}`)
      buscaCursos();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaCurso = async () => {
    try{
      let id = idCurso;
      const response = await axios.put(`http://localhost:3002/curso/${id}`, {
        id:id,
        descricao: novoCurso
      });
      buscaCursos();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  };

  return (<>
    <ul>
      {cursos.map((curso) => {
        return <li key={curso.id}>
          {curso.id} - {curso.descricao}
          <button
            style={{ marginLeft: 10 }}
            onClick={() => setIdCurso(curso.id)}
          >
            Editar
          </button>

          <button
            style={{ marginLeft: 10 }}
            onClick={() => { deletaCurso(curso.id); }}
            className="btnExcluir"
          >
            Excluir
          </button>
        </li>;
      })}
    </ul>
    <h3>{idCurso ? "Atualizar curso" : "Cadastrar novo curso"}</h3>

    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do curso: </label>
        <input type="text" value={novoCurso} onChange={(event) => setNovoCurso(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <button onClick={cadastrarCurso} disabled={idCurso !== ""}>
          Cadastrar
        </button>

        <button onClick={atualizaCurso} disabled={idCurso === ""}>
          Atualizar
        </button>
      </Stack>
    </Stack>
  </>)

}
