import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function ProfessorCcr() {
  const [professorCcrs, setProfessorCcrs] = useState([]);
  const [novoIdProfessor, setNovoIdProfessor] = useState("");
  const [novoIdCcr, setNovoIdCcr] = useState("");


  const buscaProfessorCcrs = async () => {
    try {
      const response = await axios.get("http://localhost:3002/professorCcr/");
      console.log(response.data);
      setProfessorCcrs(response.data.professorCcrs);
    }
    catch (error) {
      console.log(error);
    }
  }

  useEffect(
    () => {
      buscaProfessorCcrs();
    },
    []
  )

  const cadastrarProfessorCcr = async () => {
    const response = await axios.post("http://localhost:3002/professorCcr", {
      id_professor: novoIdProfessor,
      id_ccr: novoIdCcr
    });
    console.log(response.data)
  }


  return (<>
    <ul>
      {professorCcrs.map((professorCcr) => {
        return <li key={professorCcr.id_ccr}>{professorCcr.Professor.nome} - {professorCcr.Ccr.descricao}</li>;
      })}
    </ul>
    <Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Id do Professor: </label>
        <input type="text" value={novoIdProfessor} onChange={(event) => setNovoIdProfessor(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Id do Ccr: </label>
        <input type="text" value={novoIdCcr} onChange={(event) => setNovoIdCcr(event.target.value)} />
      </Stack>
      <button onClick={cadastrarProfessorCcr} type="submit">Cadastrar Professor-Ccr</button>
    </Stack>
  </>)

}
