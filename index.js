const express = require("express");
const app = express();
const port = 3000;

app.set("view engine", "ejs");
app.use(express.static("public"));

app.get("/", (req, res) => {
  console.log("Alınan veri:", req.body);
  res.render("dashboard", {
    user: "Adi Soyadi",
    celsius: "16",
    metre: "4",
    ae: "44",
  });
});

app.listen(port, () => {
  console.log(`Uygulama http://localhost:${port} adresinde çalışıyor`);
});
