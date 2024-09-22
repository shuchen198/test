const axios = require('axios');

const updateSpot = async (id) => {
  const isOccupied = Math.random() < 0.5; // 随机生成占用状态
  await axios.post('http://localhost:3000/api/update-spot', { id, isOccupied });
};

const simulateHardware = () => {
  setInterval(() => {
    for (let i = 1; i <= 10; i++) {
      updateSpot(`A${i}`);
    }
  }, 10000); // 每10秒更新一次
};

simulateHardware();