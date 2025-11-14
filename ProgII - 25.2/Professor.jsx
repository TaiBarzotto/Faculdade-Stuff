import { useState, useEffect } from 'react'
import axios from "axios"
import Stack from '@mui/material/Stack';


export default function Professor() {
  const [professores, setProfessores] = useState([]);
  const [novoProfessor, setNovoProfessor] = useState("");
  const [novoProfessorEmail, setNovoProfessorEmail] = useState("");


  const buscaProfessores = async () => {
    try {
      const response = await axios.get("http://localhost:3002/professor/todos");
      console.log(response.data);
      setProfessores(response.data.professores);
    }
    catch (error){
      console.log(error);
      setProfessores([]);
    }
  }

  useEffect(
    () => {
      buscaProfessores();
    },
    []
  )

  const cadastrarProfessor = async () => {
    const response = await axios.post("http://localhost:3002/professor", {
      nome: novoProfessor,
      email: novoProfessorEmail
    });
    console.log(response.data)
  }


  return (<>
      {professores !== undefined && professores.length >0 && <ul>
      {professores.map((professor) => {
        return <li key={professor.id}>{professor.nome}</li>;
      })}
    </ul>}
<Stack spacing={1}>
      <Stack spacing={1} direction="row">
        <label>Nome do Professor: </label>
        <input type="text" value={novoProfessor} onChange={(event) => setNovoProfessor(event.target.value)} />
      </Stack>
      <Stack spacing={1} direction="row">
        <label>Email do Professor: </label>
        <input type="text" value={novoProfessorEmail} onChange={(event) => setNovoProfessorEmail(event.target.value)} />
      </Stack>
      <button onClick={cadastrarProfessor} type="submit">Cadastrar Professor</button>
    </Stack>
    </>)

}
