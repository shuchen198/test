const express = require('express');
const mongoose = require('mongoose');
const app = express();

mongoose.connect('mongodb://localhost/parking_system', { useNewUrlParser: true, useUnifiedTopology: true });

const ParkingSpot = mongoose.model('ParkingSpot', {
  id: String,
  isOccupied: Boolean,
});

app.get('/api/parking-spots', async (req, res) => {
  const spots = await ParkingSpot.find();
  res.json(spots);
});

// 模拟硬件接口
app.post('/api/update-spot', express.json(), async (req, res) => {
  const { id, isOccupied } = req.body;
  await ParkingSpot.findOneAndUpdate({ id }, { isOccupied }, { upsert: true });
  res.sendStatus(200);
});

// 添加新的路由来接收考试数据
app.post('/api/exam-results', async (req, res) => {
  try {
    // 假设我们使用MongoDB存储数据
    const result = await db.collection('examResults').insertOne(req.body);
    res.status(201).json({ message: '考试数据已保存', id: result.insertedId });
  } catch (error) {
    res.status(500).json({ message: '保存数据时出错', error: error.message });
  }
});

// 添加新的路由来获取分析结果
app.get('/api/exam-analysis', async (req, res) => {
  try {
    // 这里进行数据分析的逻辑
    const analysis = await analyzeExamResults();
    res.json(analysis);
  } catch (error) {
    res.status(500).json({ message: '分析数据时出错', error: error.message });
  }
});

app.listen(3000, () => console.log('Server running on port 3000'));