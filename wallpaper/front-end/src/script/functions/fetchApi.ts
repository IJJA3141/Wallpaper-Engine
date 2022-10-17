interface disc {
  fs: string;
  type: string;
  size: number;
  used: number;
  available: number;
  use: number;
  mount: string;
}

interface data {
  cpu: number;
  gpu: number;
  mem: number;
  disc: Array<disc>;
}

async function getData(data: Array<string>) {
  return fetch("http://127.0.0.1:3000/api", {
    method: "post",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(data),
  }).then((res) => {
    return res.json();
  });
}

export { getData, data };