import React, { useState, useEffect } from 'react';
import axios from 'axios';
import ParkingLot from './components/ParkingLot';
import './App.css';

interface ParkingSpot {
  id: string;
  isOccupied: boolean;
}

function ExamAnalysis() {
  const [analysisData, setAnalysisData] = useState(null);

  useEffect(() => {
    fetch('/api/exam-analysis')
      .then(response => response.json())
      .then(data => setAnalysisData(data))
      .catch(error => console.error('获取分析数据失败:', error));
  }, []);

  if (!analysisData) return <div>加载中...</div>;

  return (
    <div>
      <h2>考试分析结果</h2>
      {/* 这里根据实际的分析数据结构来渲染内容 */}
    </div>
  );
}

function App() {
  const [parkingSpots, setParkingSpots] = useState<ParkingSpot[]>([]);

  useEffect(() => {
    const fetchParkingSpots = async () => {
      try {
        const response = await axios.get<ParkingSpot[]>('http://localhost:5000/api/parking-spots');
        setParkingSpots(response.data);
      } catch (error) {
        console.error('Error fetching parking spots:', error);
      }
    };

    fetchParkingSpots();
    const interval = setInterval(fetchParkingSpots, 5000);

    return () => clearInterval(interval);
  }, []);

  return (
    <div className="App">
      <h1>小区停车位状态</h1>
      <ParkingLot spots={parkingSpots} />
      <ExamAnalysis />
    </div>
  );
}

export default App;