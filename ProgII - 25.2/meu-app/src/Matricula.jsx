import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Matricula() {
  const [matriculas, setMatriculas] = useState([]);
  const [novoMatriculaIdAluno, setNovoMatriculaIdAluno] = useState("");
  const [novoMatriculaIdCurso, setNovoMatriculaIdCurso] = useState("");
  const [idMatricula, setIdMatricula] = useState("");


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
    try{
      const response = await axios.post("http://localhost:3002/matricula", {
        id_aluno: novoMatriculaIdAluno,
        id_curso: novoMatriculaIdCurso
      });
      buscaMatriculas();
      console.log(response.data)
    } catch(error){
      console.log(error);
    }
  }

  const deletaMatricula = async (id) => {
    try {
      await axios.delete(`http://localhost:3002/matricula/${id}`)
      buscaMatriculas();
    } catch (error) {
      console.log(error);
    }
  };

  const atualizaMatricula = async () => {
    try {
      let id = novoMatriculaIdAluno;
      const response = await axios.put(`http://localhost:3002/matricula/${id}`, {
        id_aluno: novoMatriculaIdAluno,
        id_curso: novoMatriculaIdCurso
      });
      buscaMatriculas();
      console.log(response.data)
    } catch (error){
      console.log(error);
    }
};

return (<>
  <ul>
    {matriculas.map((matricula) => {
      return <li key={matricula.id_aluno}>{matricula.Aluno.nome} - {matricula.Curso.descricao}
        <button
          style={{ marginLeft: 10 }}
          onClick={() => setIdMatricula(matricula.id_aluno)}
        >
          Editar
        </button>

        <button
          style={{ marginLeft: 10 }}
          className="btnExcluir"
            onClick={() => { deletaMatricula(matricula.id_aluno); }}
        >
          Excluir
        </button>
      </li>;
    })}
  </ul>
  <h3>{idMatricula ? "Atualizar matricula" : "Cadastrar novo matricula"}</h3>

  <Stack spacing={1}>
    <Stack spacing={1} direction="row">
      <label>Id do aluno: </label>
      <input type="text" value={novoMatriculaIdAluno} onChange={(event) => setNovoMatriculaIdAluno(event.target.value)} />
    </Stack>
    <Stack spacing={1} direction="row">
      <label>Id do Curso: </label>
      <input type="text" value={novoMatriculaIdCurso} onChange={(event) => setNovoMatriculaIdCurso(event.target.value)} />
    </Stack>
    <Stack spacing={1} direction="row">
      <button onClick={cadastrarMatricula} disabled={idMatricula !== ""}>
        Cadastrar
      </button>

      <button onClick={atualizaMatricula} disabled={idMatricula === ""}>
        Atualizar
      </button>
    </Stack>
  </Stack>

</>)

}
